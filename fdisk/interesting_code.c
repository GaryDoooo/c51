/* I have created this struct to store options (in short and long form)
 * and help in the same variable. The struct option array, wich is
 * needed for getopt_long is build dynamically by build_option_table()
 * using this array. We can add options here there isn't problems
 * with getopt_long() */
struct {
	char *id;
	int has_arg;
	int *flag;
	int val;
	char *help;
} extd_options[] = {
  /* name   has_arg      flag  val  help */
  { "help", no_argument, NULL, 'h', "displays this help message"},
  { "list", no_argument, NULL, 'l', "list partition table(s)"},
  { "raw-print", no_argument, NULL, 'r', "show the raw data in the partition table(s)"},
  { "size", required_argument, NULL, 's', "show partition size"},
#ifdef GNU_EXT
  {	"linux-fdisk", no_argument, NULL, 'L', "enable Linux fdisk compatibility mode"},
  { "gnu-fdisk", no_argument, NULL, 'G', "disable Linux fdisk compatibility mode"},
#endif /* GNU_EXT */
  { "interactive", no_argument, NULL, 'i', "where necessary, prompts for user intervention"},
  { "script", no_argument, NULL, 'p', "never prompts for user intervention"},
#ifdef GNU_EXT
  { "align", required_argument, NULL, 'A', "specify align to be none, cyl, min or opt"},
#endif
  { "sector-units", no_argument, NULL, 'u', "use sectors instead of cylinder as a default unit"},
  { "sector-size", required_argument, NULL, 'b', "specify the sector size in bytes"},
  { "cylinders", required_argument, NULL, 'C', "specify the number of cylinders, actually does nothing"},
  { "heads", required_argument, NULL, 'H', "in lfdisk, specify the number of heads of the disk"},
  { "sectors", required_argument, NULL, 'S', "in lfdisk, specify the number of sectors per track"},
  { "list-partition-types", no_argument, NULL, 't', "displays a list of supported partition types"},
  { "version", no_argument, NULL, 'v', "displays the version"},
  
  /* Last element must be NULL */
  { NULL, 0, NULL, 0, NULL}
};

//static PedTimer* timer;
static TimerContext timer_context;
static FdiskCommand* fdisk_main_menu_commands[256] = {NULL};
static FdiskCommand* fdisk_ex_menu_commands[256] = {NULL};
static FdiskCommand* fdisk_bsd_menu_commands[256] = {NULL};
static int in_menu = 0;

static int
getstring (const char* prompt, char** value, const StrList* words,
	   const StrList* locwords, int multi_word)
{
	char*		def_str = NULL;
	char*		input;
	StrList*	valid = NULL;
	const StrList*	walk;
	const StrList*	locwalk;
	char*		fix_result = NULL;

	/* TODO: Add a function that does just this to strlist.c */
	valid = str_list_join (str_list_duplicate(words),
	                       str_list_duplicate(locwords));

	if (*value) def_str = strdup(*value);
	input = fdisk_command_line_get_word (prompt, def_str,
				             valid, multi_word);

	str_list_destroy(valid);
	if (def_str) free(def_str);

	/* If the user has choosen a localised string, we should return the
	   non-localized one, corresponding to it */
	for (walk = words, locwalk = locwords; walk && locwalk;
	     walk = walk->next, locwalk = locwalk->next)
	{
		/* If it matches a non-localised string, we are happy */
		if (str_list_match_node(walk, input)) {
			if (fix_result)
				free(fix_result);
			fix_result = NULL;
			break;
		}
		/* If it matches a localised string, we save the non-localised
		   one, but we don't break */
		if (!fix_result && str_list_match_node(locwalk, input)) {
			fix_result = str_list_convert_node(walk);
		}
	}
	if (fix_result) {
		free(input);
		*value = fix_result;
	}
	else
		*value = input;
	return 1;
}

/* We might as well get rid of this one */
static int
getbool (const char* prompt, int* value)
{
	*value = command_line_prompt_boolean_question (prompt);
	return 1;
}

void
fdisk_print_options_help ()
{
	unsigned int i;
	for(i=0; extd_options[i].id != NULL; i++)
		printf("  -%c, --%-23.23s %s\n", extd_options[i].val, extd_options[i].id, _(extd_options[i].help));
}

void
fdisk_print_commands_help (FdiskCommand* cmds[])
{
	 int		i;

	if (cmds) {
		for (i=0; cmds [i]; i++)
			fdisk_command_print_summary (cmds [i]);
	} else {
		if (in_menu == 0) {
			for (i=0; fdisk_main_menu_commands [i]; i++)
				fdisk_command_print_summary (fdisk_main_menu_commands [i]);
		}
		else if (in_menu == 1) {
			for (i=0; fdisk_ex_menu_commands [i]; i++)
				fdisk_command_print_summary (fdisk_ex_menu_commands [i]);
    		}
		else if (in_menu == 2) {
			for (i=0; fdisk_bsd_menu_commands [i]; i++)
				fdisk_command_print_summary (fdisk_bsd_menu_commands [i]);
    		}
	}
}

char*
fdisk_command_line_get_word (const char* prompt, const char* def,
		       const StrList* possibilities, int multi_word)
{
	do {
		if (fdisk_command_line_get_word_count ()) {
			char*		result = fdisk_command_line_pop_word ();
			StrList*	result_node;

			if (!possibilities)
				return result;
			result_node = str_list_match (possibilities, result);
			free (result);
			if (result_node)
				return str_list_convert_node (result_node);
			fdisk_command_line_flush ();
		}

		fdisk_command_line_prompt_words (prompt, def, possibilities,
						multi_word);
	} while (fdisk_command_line_get_word_count ());

	return NULL;
}

int
fdisk_command_line_get_word_count ()
{
	return str_list_length (command_line);
}

int
fdisk_command_line_get_integer (const char* prompt, int* value)
{
	char	def_str [12];
	char*	input;
	int	valid;

	snprintf (def_str, sizeof(def_str), "%d", *value);
	input = fdisk_command_line_get_word (prompt, *value ? def_str : NULL,
				       NULL, 1);
	if (!input)
		return 0;
	valid = sscanf (input, "%d", value);
	free (input);
	return valid;
}

static int
do_help(PedDisk** disk)
{
	puts(_("Command action"));
	if (in_menu == 0)
		fdisk_print_commands_help(fdisk_main_menu_commands);
	else if (in_menu == 1)
		fdisk_print_commands_help(fdisk_ex_menu_commands);
	else if (in_menu == 2)
	        fdisk_print_commands_help(fdisk_bsd_menu_commands);
	return 1;
}
