




<!DOCTYPE html>
<html class="   ">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    
    
    <title>stc-isp/uart.c at master · van9ogh/stc-isp · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <meta property="fb:app_id" content="1401488693436528"/>

      <meta content="@github" name="twitter:site" /><meta content="summary" name="twitter:card" /><meta content="van9ogh/stc-isp" name="twitter:title" /><meta content="stc-isp - An command line STC 8051 ISP programmer for linux" name="twitter:description" /><meta content="https://avatars3.githubusercontent.com/u/1551572?s=400" name="twitter:image:src" />
<meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="https://avatars3.githubusercontent.com/u/1551572?s=400" property="og:image" /><meta content="van9ogh/stc-isp" property="og:title" /><meta content="https://github.com/van9ogh/stc-isp" property="og:url" /><meta content="stc-isp - An command line STC 8051 ISP programmer for linux" property="og:description" />

    <link rel="assets" href="https://github.global.ssl.fastly.net/">
    <link rel="conduit-xhr" href="https://ghconduit.com:25035/">
    <link rel="xhr-socket" href="/_sockets" />

    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="4C71ACCD:1FFF:B31806:536484EB" name="octolytics-dimension-request_id" />
    

    
    
    <link rel="icon" type="image/x-icon" href="https://github.global.ssl.fastly.net/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="voxY5JgChJyNQlCryymqwy9P5/1v4LMNo/IB7XF7HsQhVTeiR9+Ek5+vNmG0n5fmcD7zAXuKr07JeT7F8D5kjw==" name="csrf-token" />

    <link href="https://github.global.ssl.fastly.net/assets/github-825241e13de547a733c8a9cc535c8f6b411b52c1.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://github.global.ssl.fastly.net/assets/github2-0c03a1f6ffa15e379ec26513a90980fce28e78d9.css" media="all" rel="stylesheet" type="text/css" />
    


        <script crossorigin="anonymous" src="https://github.global.ssl.fastly.net/assets/frameworks-704d4dc7cea097536a718a880e8a845b49314e5b.js" type="text/javascript"></script>
        <script async="async" crossorigin="anonymous" src="https://github.global.ssl.fastly.net/assets/github-d72adf5c07eb3ac77dc24e8783e70eb92d281e85.js" type="text/javascript"></script>
        
        
      <meta http-equiv="x-pjax-version" content="01c97dfede8e115547d9c4a886c060dc">

      
  <meta name="description" content="stc-isp - An command line STC 8051 ISP programmer for linux" />

  <meta content="1551572" name="octolytics-dimension-user_id" /><meta content="van9ogh" name="octolytics-dimension-user_login" /><meta content="6588959" name="octolytics-dimension-repository_id" /><meta content="van9ogh/stc-isp" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="6588959" name="octolytics-dimension-repository_network_root_id" /><meta content="van9ogh/stc-isp" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/van9ogh/stc-isp/commits/master.atom" rel="alternate" title="Recent Commits to stc-isp:master" type="application/atom+xml" />

  </head>


  <body class="logged_out  env-production  vis-public page-blob">
    <a href="#start-of-content" tabindex="1" class="accessibility-aid js-skip-to-content">Skip to content</a>
    <div class="wrapper">
      
      
      
      


      
      <div class="header header-logged-out">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/">
      <span class="mega-octicon octicon-logo-github"></span>
    </a>

    <div class="header-actions">
        <a class="button primary" href="/join">Sign up</a>
      <a class="button signin" href="/login?return_to=%2Fvan9ogh%2Fstc-isp%2Fblob%2Fmaster%2Fuart.c">Sign in</a>
    </div>

    <div class="command-bar js-command-bar  in-repository">

      <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
        <li class="features"><a href="/features">Features</a></li>
          <li class="enterprise"><a href="https://enterprise.github.com/">Enterprise</a></li>
          <li class="blog"><a href="/blog">Blog</a></li>
      </ul>
        <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<div class="commandbar">
  <span class="message"></span>
  <input type="text" data-hotkey="s, /" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    
      data-repo="van9ogh/stc-isp"
      data-branch="master"
      data-sha="2c5913f04c50a089bb5371d595731efc03df8f6b"
  >
  <div class="display hidden"></div>
</div>

    <input type="hidden" name="nwo" value="van9ogh/stc-isp" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target" role="button" aria-haspopup="true">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container" aria-hidden="true">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="help tooltipped tooltipped-s" aria-label="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
    </div>

  </div>
</div>



      <div id="start-of-content" class="accessibility-aid"></div>
          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    <div id="js-flash-container">
      
    </div>
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">


  <li>
    <a href="/login?return_to=%2Fvan9ogh%2Fstc-isp"
    class="minibutton with-count star-button tooltipped tooltipped-n"
    aria-label="You must be signed in to star a repository" rel="nofollow">
    <span class="octicon octicon-star"></span>Star
  </a>

    <a class="social-count js-social-count" href="/van9ogh/stc-isp/stargazers">
      9
    </a>

  </li>

    <li>
      <a href="/login?return_to=%2Fvan9ogh%2Fstc-isp"
        class="minibutton with-count js-toggler-target fork-button tooltipped tooltipped-n"
        aria-label="You must be signed in to fork a repository" rel="nofollow">
        <span class="octicon octicon-git-branch"></span>Fork
      </a>
      <a href="/van9ogh/stc-isp/network" class="social-count">
        4
      </a>
    </li>
</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo"></span>
          <span class="author"><a href="/van9ogh" class="url fn" itemprop="url" rel="author"><span itemprop="title">van9ogh</span></a></span><!--
       --><span class="path-divider">/</span><!--
       --><strong><a href="/van9ogh/stc-isp" class="js-current-repository js-repo-home-link">stc-isp</a></strong>

          <span class="page-context-loader">
            <img alt="Octocat-spinner-32" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">
      <div class="repository-with-sidebar repo-container new-discussion-timeline js-new-discussion-timeline  ">
        <div class="repository-sidebar clearfix">
            

<div class="sunken-menu vertical-right repo-nav js-repo-nav js-repository-container-pjax js-octicon-loaders">
  <div class="sunken-menu-contents">
    <ul class="sunken-menu-group">
      <li class="tooltipped tooltipped-w" aria-label="Code">
        <a href="/van9ogh/stc-isp" aria-label="Code" class="selected js-selected-navigation-item sunken-menu-item" data-hotkey="g c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /van9ogh/stc-isp">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped tooltipped-w" aria-label="Issues">
          <a href="/van9ogh/stc-isp/issues" aria-label="Issues" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g i" data-selected-links="repo_issues /van9ogh/stc-isp/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class='counter'>1</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped tooltipped-w" aria-label="Pull Requests">
        <a href="/van9ogh/stc-isp/pulls" aria-label="Pull Requests" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-hotkey="g p" data-selected-links="repo_pulls /van9ogh/stc-isp/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>0</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


        <li class="tooltipped tooltipped-w" aria-label="Wiki">
          <a href="/van9ogh/stc-isp/wiki" aria-label="Wiki" class="js-selected-navigation-item sunken-menu-item" data-hotkey="g w" data-pjax="true" data-selected-links="repo_wiki /van9ogh/stc-isp/wiki">
            <span class="octicon octicon-book"></span> <span class="full-word">Wiki</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>
    </ul>
    <div class="sunken-menu-separator"></div>
    <ul class="sunken-menu-group">

      <li class="tooltipped tooltipped-w" aria-label="Pulse">
        <a href="/van9ogh/stc-isp/pulse" aria-label="Pulse" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="pulse /van9ogh/stc-isp/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Graphs">
        <a href="/van9ogh/stc-isp/graphs" aria-label="Graphs" class="js-selected-navigation-item sunken-menu-item" data-pjax="true" data-selected-links="repo_graphs repo_contributors /van9ogh/stc-isp/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped tooltipped-w" aria-label="Network">
        <a href="/van9ogh/stc-isp/network" aria-label="Network" class="js-selected-navigation-item sunken-menu-item js-disable-pjax" data-selected-links="repo_network /van9ogh/stc-isp/network">
          <span class="octicon octicon-git-branch"></span> <span class="full-word">Network</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


  </div>
</div>

              <div class="only-with-full-nav">
                

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><strong>HTTPS</strong> clone URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/van9ogh/stc-isp.git" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/van9ogh/stc-isp.git" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><strong>Subversion</strong> checkout URL</h3>
  <div class="clone-url-box">
    <input type="text" class="clone js-url-field"
           value="https://github.com/van9ogh/stc-isp" readonly="readonly">
    <span class="url-box-clippy">
    <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="https://github.com/van9ogh/stc-isp" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>


<p class="clone-options">You can clone with
      <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>
      or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <span class="help tooltipped tooltipped-n" aria-label="Get help on which URL is right for you.">
    <a href="https://help.github.com/articles/which-remote-url-should-i-use">
    <span class="octicon octicon-question"></span>
    </a>
  </span>
</p>



                <a href="/van9ogh/stc-isp/archive/master.zip"
                   class="minibutton sidebar-button"
                   aria-label="Download van9ogh/stc-isp as a zip file"
                   title="Download van9ogh/stc-isp as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
              </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          

<a href="/van9ogh/stc-isp/blob/e73fd4ee1683ab34f4880e4ac3891fffdfc152be/uart.c" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:24d340056c47d8e7975b0dc002cbf11d -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/van9ogh/stc-isp/find/master" data-pjax data-hotkey="t" class="js-show-file-finder" style="display:none">Show File Finder</a>

<div class="file-navigation">
  

<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="master"
    data-ref="master"
    role="button" aria-label="Switch branches or tags" tabindex="0" aria-haspopup="true">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button">master</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax aria-hidden="true">

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-remove-close js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/van9ogh/stc-isp/blob/gh-pages/uart.c"
                 data-name="gh-pages"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target"
                 title="gh-pages">gh-pages</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/van9ogh/stc-isp/blob/master/uart.c"
                 data-name="master"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target"
                 title="master">master</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/van9ogh/stc-isp" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">stc-isp</span></a></span></span><span class="separator"> / </span><strong class="final-path">uart.c</strong> <button aria-label="copy to clipboard" class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="uart.c" data-copied-hint="copied!" type="button"><span class="octicon octicon-clippy"></span></button>
  </div>
</div>


  <div class="commit commit-loader file-history-tease js-deferred-content" data-url="/van9ogh/stc-isp/contributors/master/uart.c">
    Fetching contributors…

    <div class="participation">
      <p class="loader-loading"><img alt="Octocat-spinner-32-eaf2f5" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32-EAF2F5.gif" width="16" /></p>
      <p class="loader-error">Cannot retrieve contributors at this time</p>
    </div>
  </div>

<div class="file-box">
  <div class="file">
    <div class="meta clearfix">
      <div class="info file-name">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">file</span>
        <span class="meta-divider"></span>
          <span>345 lines (308 sloc)</span>
          <span class="meta-divider"></span>
        <span>7.625 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
              <a class="minibutton disabled tooltipped tooltipped-w" href="#"
                 aria-label="You must be signed in to make or propose changes">Edit</a>
          <a href="/van9ogh/stc-isp/raw/master/uart.c" class="button minibutton " id="raw-url">Raw</a>
            <a href="/van9ogh/stc-isp/blame/master/uart.c" class="button minibutton js-update-url-with-hash">Blame</a>
          <a href="/van9ogh/stc-isp/commits/master/uart.c" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->
          <a class="minibutton danger disabled empty-icon tooltipped tooltipped-w" href="#"
             aria-label="You must be signed in to make or propose changes">
          Delete
        </a>
      </div><!-- /.actions -->
    </div>
        <div class="blob-wrapper data type-c js-blob-data">
        <table class="file-code file-diff tab-size-8">
          <tr class="file-code-line">
            <td class="blob-line-nums">
              <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>
<span id="L314" rel="#L314">314</span>
<span id="L315" rel="#L315">315</span>
<span id="L316" rel="#L316">316</span>
<span id="L317" rel="#L317">317</span>
<span id="L318" rel="#L318">318</span>
<span id="L319" rel="#L319">319</span>
<span id="L320" rel="#L320">320</span>
<span id="L321" rel="#L321">321</span>
<span id="L322" rel="#L322">322</span>
<span id="L323" rel="#L323">323</span>
<span id="L324" rel="#L324">324</span>
<span id="L325" rel="#L325">325</span>
<span id="L326" rel="#L326">326</span>
<span id="L327" rel="#L327">327</span>
<span id="L328" rel="#L328">328</span>
<span id="L329" rel="#L329">329</span>
<span id="L330" rel="#L330">330</span>
<span id="L331" rel="#L331">331</span>
<span id="L332" rel="#L332">332</span>
<span id="L333" rel="#L333">333</span>
<span id="L334" rel="#L334">334</span>
<span id="L335" rel="#L335">335</span>
<span id="L336" rel="#L336">336</span>
<span id="L337" rel="#L337">337</span>
<span id="L338" rel="#L338">338</span>
<span id="L339" rel="#L339">339</span>
<span id="L340" rel="#L340">340</span>
<span id="L341" rel="#L341">341</span>
<span id="L342" rel="#L342">342</span>
<span id="L343" rel="#L343">343</span>
<span id="L344" rel="#L344">344</span>

            </td>
            <td class="blob-line-code"><div class="code-body highlight"><pre><div class='line' id='LC1'><span class="cp">#include &lt;termios.h&gt;</span></div><div class='line' id='LC2'><span class="cp">#include &lt;fcntl.h&gt;</span></div><div class='line' id='LC3'><span class="cp">#include &lt;stdio.h&gt;</span></div><div class='line' id='LC4'><span class="cp">#include &lt;string.h&gt;</span></div><div class='line' id='LC5'><span class="cp">#include &quot;uart.h&quot;</span></div><div class='line' id='LC6'><br/></div><div class='line' id='LC7'><br/></div><div class='line' id='LC8'><span class="cm">/*</span></div><div class='line' id='LC9'><span class="cm">***********************************************************</span></div><div class='line' id='LC10'><span class="cm">* printf_uart</span></div><div class='line' id='LC11'><span class="cm">* print out the bytes sent to(received from) uart</span></div><div class='line' id='LC12'><span class="cm">* buf:    the bytes to be print out</span></div><div class='line' id='LC13'><span class="cm">* len:    how many bytes do you want to see?</span></div><div class='line' id='LC14'><span class="cm">* return: NULL</span></div><div class='line' id='LC15'><span class="cm">***********************************************************</span></div><div class='line' id='LC16'><span class="cm">*/</span></div><div class='line' id='LC17'><span class="kt">void</span> <span class="nf">printf_uart</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">char</span> <span class="o">*</span><span class="n">buf</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">len</span><span class="p">)</span></div><div class='line' id='LC18'><span class="p">{</span></div><div class='line' id='LC19'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC20'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">for</span> <span class="p">(</span><span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">len</span><span class="p">;</span> <span class="n">i</span> <span class="o">++</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC21'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="o">!</span> <span class="p">(</span><span class="n">i</span> <span class="o">%</span> <span class="mi">16</span><span class="p">))</span> <span class="p">{</span></div><div class='line' id='LC22'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">i</span><span class="p">)</span> <span class="n">printf</span><span class="p">(</span><span class="s">&quot;</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC23'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;%04X: &quot;</span><span class="p">,</span> <span class="n">i</span><span class="p">);</span></div><div class='line' id='LC24'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC25'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;%02X &quot;</span><span class="p">,</span> <span class="n">buf</span><span class="p">[</span><span class="n">i</span><span class="p">]);</span></div><div class='line' id='LC26'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC27'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;</span><span class="se">\n\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC28'><span class="p">}</span></div><div class='line' id='LC29'><br/></div><div class='line' id='LC30'><span class="cm">/*</span></div><div class='line' id='LC31'><span class="cm">***********************************************************</span></div><div class='line' id='LC32'><span class="cm">* open_uart</span></div><div class='line' id='LC33'><span class="cm">* open the uart </span></div><div class='line' id='LC34'><span class="cm">* prot:    the uart file name, like &quot;/dev/ttyS0&quot;</span></div><div class='line' id='LC35'><span class="cm">* oldtio:  the struct termios to save the old setting </span></div><div class='line' id='LC36'><span class="cm">*          with uart</span></div><div class='line' id='LC37'><span class="cm">* baud:    the baud rate to set to the uart, </span></div><div class='line' id='LC38'><span class="cm">*          default is 9600</span></div><div class='line' id='LC39'><span class="cm">* databit: the num of the data bits</span></div><div class='line' id='LC40'><span class="cm">* stopbit: the num of the stop bits , can be 1 or 2</span></div><div class='line' id='LC41'><span class="cm">* parity:  parity of the uart, 0 None, 1 Odd, 2 Even,</span></div><div class='line' id='LC42'><span class="cm">*                              3 Make, 4 Space</span></div><div class='line' id='LC43'><span class="cm">* flow:    flow of the uart, 0 None, 1 Hardware, </span></div><div class='line' id='LC44'><span class="cm">*                            2 Software</span></div><div class='line' id='LC45'><span class="cm">* return:  uart file description if success, </span></div><div class='line' id='LC46'><span class="cm">*          or -1 if error</span></div><div class='line' id='LC47'><span class="cm">***********************************************************</span></div><div class='line' id='LC48'><span class="cm">*/</span></div><div class='line' id='LC49'><span class="kt">int</span> <span class="nf">open_uart</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">char</span> <span class="o">*</span><span class="n">port</span><span class="p">,</span> <span class="k">struct</span> <span class="n">termios</span> <span class="o">*</span><span class="n">oldtio</span><span class="p">,</span> <span class="kt">int</span> <span class="n">baud</span><span class="p">,</span> <span class="kt">int</span> <span class="n">databit</span><span class="p">,</span> <span class="kt">int</span> <span class="n">stopbit</span><span class="p">,</span> <span class="kt">int</span> <span class="n">parity</span><span class="p">,</span> <span class="kt">int</span> <span class="n">flow</span><span class="p">)</span></div><div class='line' id='LC50'><span class="p">{</span></div><div class='line' id='LC51'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">fd</span><span class="p">;</span></div><div class='line' id='LC52'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">termios</span> <span class="n">termios_p</span><span class="p">;</span></div><div class='line' id='LC53'><br/></div><div class='line' id='LC54'>	<span class="n">fd</span> <span class="o">=</span> <span class="n">open</span><span class="p">(</span><span class="n">port</span><span class="p">,</span> <span class="n">O_RDWR</span> <span class="o">|</span> <span class="n">O_NOCTTY</span> <span class="o">|</span> <span class="n">O_NDELAY</span> <span class="p">);</span></div><div class='line' id='LC55'><br/></div><div class='line' id='LC56'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span> <span class="n">fd</span>  <span class="o">&lt;</span> <span class="mi">0</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC57'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">perror</span><span class="p">(</span><span class="s">&quot;Open com error:</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC58'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//char buff[512];</span></div><div class='line' id='LC59'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//snprintf(buff, 512, &quot;&lt;b&gt;Open com error!&lt;/b&gt;\n\n&quot;</span></div><div class='line' id='LC60'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//&quot;&lt;b&gt;Please: chmod 666 %s or make sure it&#39;s ok!&lt;/b&gt;&quot;, port);</span></div><div class='line' id='LC61'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//create_xgcom_msg(maindata-&gt;gmain, buff);</span></div><div class='line' id='LC62'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC63'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC64'>	<span class="n">printf</span><span class="p">(</span><span class="s">&quot;Open %s </span><span class="se">\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="n">port</span><span class="p">);</span></div><div class='line' id='LC65'><br/></div><div class='line' id='LC66'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">oldtio</span> <span class="o">!=</span> <span class="mi">0</span><span class="p">)</span></div><div class='line' id='LC67'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">tcgetattr</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">oldtio</span><span class="p">);</span></div><div class='line' id='LC68'><br/></div><div class='line' id='LC69'>	<span class="k">switch</span> <span class="p">(</span><span class="n">baud</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC70'>		<span class="k">case</span> <span class="mi">300</span>:</div><div class='line' id='LC71'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B300</span><span class="p">;</span></div><div class='line' id='LC72'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC73'>		<span class="k">case</span> <span class="mi">600</span>:</div><div class='line' id='LC74'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B600</span><span class="p">;</span></div><div class='line' id='LC75'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC76'>		<span class="k">case</span> <span class="mi">1200</span>:</div><div class='line' id='LC77'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B1200</span><span class="p">;</span></div><div class='line' id='LC78'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC79'>		<span class="k">case</span> <span class="mi">2400</span>:</div><div class='line' id='LC80'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B2400</span><span class="p">;</span></div><div class='line' id='LC81'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC82'>		<span class="k">case</span> <span class="mi">4800</span>:</div><div class='line' id='LC83'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B4800</span><span class="p">;</span></div><div class='line' id='LC84'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC85'>		<span class="k">case</span> <span class="mi">9600</span>:</div><div class='line' id='LC86'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B9600</span><span class="p">;</span></div><div class='line' id='LC87'>			<span class="c1">//cfsetispeed(&amp;termios_p, B9600);  </span></div><div class='line' id='LC88'>			<span class="c1">//cfsetospeed(&amp;termios_p, B9600); </span></div><div class='line' id='LC89'>			<span class="k">break</span><span class="p">;</span> </div><div class='line' id='LC90'>		<span class="k">case</span> <span class="mi">19200</span>:</div><div class='line' id='LC91'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B19200</span><span class="p">;</span></div><div class='line' id='LC92'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC93'>		<span class="k">case</span> <span class="mi">38400</span>:</div><div class='line' id='LC94'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B38400</span><span class="p">;</span></div><div class='line' id='LC95'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC96'>		<span class="k">case</span> <span class="mi">57600</span>:</div><div class='line' id='LC97'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B57600</span><span class="p">;</span></div><div class='line' id='LC98'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC99'>		<span class="k">case</span> <span class="mi">115200</span>:</div><div class='line' id='LC100'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B115200</span><span class="p">;</span></div><div class='line' id='LC101'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC102'>		<span class="nl">default:</span></div><div class='line' id='LC103'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">=</span>  <span class="n">B9600</span><span class="p">;</span></div><div class='line' id='LC104'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC105'>	<span class="p">}</span></div><div class='line' id='LC106'><br/></div><div class='line' id='LC107'>	<span class="k">switch</span> <span class="p">(</span><span class="n">databit</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC108'>		<span class="k">case</span> <span class="mi">5</span>:</div><div class='line' id='LC109'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CS5</span><span class="p">;</span></div><div class='line' id='LC110'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC111'>		<span class="k">case</span> <span class="mi">6</span>:</div><div class='line' id='LC112'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CS6</span><span class="p">;</span></div><div class='line' id='LC113'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC114'>		<span class="k">case</span> <span class="mi">7</span>:</div><div class='line' id='LC115'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CS7</span><span class="p">;</span></div><div class='line' id='LC116'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC117'>		<span class="k">case</span> <span class="mi">8</span>:</div><div class='line' id='LC118'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CS8</span><span class="p">;</span></div><div class='line' id='LC119'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC120'>		<span class="nl">default:</span></div><div class='line' id='LC121'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CS8</span><span class="p">;</span></div><div class='line' id='LC122'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC123'>	<span class="p">}</span></div><div class='line' id='LC124'>	<span class="k">switch</span> <span class="p">(</span><span class="n">parity</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC125'>		<span class="k">case</span> <span class="mi">0</span>:</div><div class='line' id='LC126'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="n">PARENB</span><span class="p">;</span> <span class="cm">/* Clear parity enable */</span></div><div class='line' id='LC127'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_iflag</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="n">INPCK</span><span class="p">;</span> <span class="cm">/* Enable parity checking */</span> </div><div class='line' id='LC128'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC129'>		<span class="k">case</span> <span class="mi">1</span>:</div><div class='line' id='LC130'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="p">(</span><span class="n">PARODD</span> <span class="o">|</span> <span class="n">PARENB</span><span class="p">);</span> <span class="cm">/* 设置为奇效验*/</span></div><div class='line' id='LC131'>			<span class="c1">//termios_p.c_iflag |= INPCK; /* Disnable parity checking */ </span></div><div class='line' id='LC132'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC133'>		<span class="k">case</span> <span class="mi">2</span>:</div><div class='line' id='LC134'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">PARENB</span><span class="p">;</span> <span class="cm">/* Enable parity */</span></div><div class='line' id='LC135'>			<span class="c1">//termios_p.c_cflag &amp;= ~PARODD; /* 转换为偶效验*/</span></div><div class='line' id='LC136'>			<span class="c1">//termios_p.c_iflag |= INPCK; /* Disnable parity checking */</span></div><div class='line' id='LC137'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC138'>		<span class="nl">default:</span></div><div class='line' id='LC139'>			<span class="c1">//termios_p.c_cflag &amp;= ~PARENB; /* Clear parity enable */</span></div><div class='line' id='LC140'>			<span class="c1">//termios_p.c_iflag &amp;= ~INPCK; /* Enable parity checking */ </span></div><div class='line' id='LC141'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC142'>	<span class="p">}</span></div><div class='line' id='LC143'>	<span class="k">switch</span> <span class="p">(</span><span class="n">stopbit</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC144'>		<span class="k">case</span> <span class="mi">1</span>:</div><div class='line' id='LC145'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="n">CSTOPB</span><span class="p">;</span> </div><div class='line' id='LC146'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC147'>		<span class="k">case</span> <span class="mi">2</span>:</div><div class='line' id='LC148'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CSTOPB</span><span class="p">;</span> </div><div class='line' id='LC149'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC150'>		<span class="nl">default:</span></div><div class='line' id='LC151'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="n">CSTOPB</span><span class="p">;</span> </div><div class='line' id='LC152'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC153'>	<span class="p">}</span></div><div class='line' id='LC154'>	<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CREAD</span><span class="p">;</span></div><div class='line' id='LC155'>	<span class="n">termios_p</span><span class="p">.</span><span class="n">c_iflag</span> <span class="o">=</span> <span class="n">IGNPAR</span> <span class="o">|</span> <span class="n">IGNBRK</span><span class="p">;</span></div><div class='line' id='LC156'>	<span class="k">switch</span> <span class="p">(</span><span class="n">flow</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC157'>		<span class="k">case</span> <span class="mi">1</span>:</div><div class='line' id='LC158'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_iflag</span> <span class="o">|=</span> <span class="p">(</span><span class="n">IXON</span> <span class="o">|</span> <span class="n">IXOFF</span> <span class="o">|</span> <span class="n">IXANY</span><span class="p">);</span> <span class="c1">//Enable Software Flow Control</span></div><div class='line' id='LC159'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC160'>		<span class="k">case</span> <span class="mi">2</span>:</div><div class='line' id='LC161'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CRTSCTS</span><span class="p">;</span>  <span class="c1">//Enable hardware flow control</span></div><div class='line' id='LC162'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC163'>		<span class="nl">default:</span></div><div class='line' id='LC164'>			<span class="c1">//termios_p.c_cflag = 0;</span></div><div class='line' id='LC165'>			<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cflag</span> <span class="o">|=</span> <span class="n">CLOCAL</span><span class="p">;</span></div><div class='line' id='LC166'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC167'>	<span class="p">}</span></div><div class='line' id='LC168'><br/></div><div class='line' id='LC169'>	<span class="n">termios_p</span><span class="p">.</span><span class="n">c_oflag</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC170'>	<span class="n">termios_p</span><span class="p">.</span><span class="n">c_lflag</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC171'>	<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cc</span><span class="p">[</span><span class="n">VTIME</span><span class="p">]</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC172'>	<span class="n">termios_p</span><span class="p">.</span><span class="n">c_cc</span><span class="p">[</span><span class="n">VMIN</span><span class="p">]</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC173'><br/></div><div class='line' id='LC174'>	<span class="n">tcsetattr</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">TCSANOW</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">termios_p</span><span class="p">);</span></div><div class='line' id='LC175'>	<span class="n">tcflush</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">TCOFLUSH</span><span class="p">);</span>  </div><div class='line' id='LC176'>	<span class="n">tcflush</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">TCIFLUSH</span><span class="p">);</span></div><div class='line' id='LC177'><br/></div><div class='line' id='LC178'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;Baudrate is %d</span><span class="se">\n\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="n">baud</span><span class="p">);</span></div><div class='line' id='LC179'><br/></div><div class='line' id='LC180'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">fd</span><span class="p">;</span>	</div><div class='line' id='LC181'><span class="p">}</span></div><div class='line' id='LC182'><br/></div><div class='line' id='LC183'><span class="cm">/*</span></div><div class='line' id='LC184'><span class="cm">***********************************************************</span></div><div class='line' id='LC185'><span class="cm">* close_uart</span></div><div class='line' id='LC186'><span class="cm">* close the uart</span></div><div class='line' id='LC187'><span class="cm">* fd:     uart file description</span></div><div class='line' id='LC188'><span class="cm">* return: NULL</span></div><div class='line' id='LC189'><span class="cm">***********************************************************</span></div><div class='line' id='LC190'><span class="cm">*/</span></div><div class='line' id='LC191'><span class="kt">void</span> <span class="nf">close_uart</span><span class="p">(</span><span class="kt">int</span> <span class="n">fd</span><span class="p">)</span></div><div class='line' id='LC192'><span class="p">{</span></div><div class='line' id='LC193'>	<span class="k">if</span> <span class="p">(</span><span class="n">fd</span> <span class="o">&gt;</span> <span class="mi">0</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC194'>		<span class="n">close</span><span class="p">(</span><span class="n">fd</span><span class="p">);</span></div><div class='line' id='LC195'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;close uart</span><span class="se">\n\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC196'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC197'><span class="p">}</span></div><div class='line' id='LC198'><br/></div><div class='line' id='LC199'><span class="cm">/*</span></div><div class='line' id='LC200'><span class="cm">***********************************************************</span></div><div class='line' id='LC201'><span class="cm">* read_uart</span></div><div class='line' id='LC202'><span class="cm">* read from uart ,save to buf</span></div><div class='line' id='LC203'><span class="cm">* fd:     uart file description</span></div><div class='line' id='LC204'><span class="cm">* buf:    save bytes received from uart</span></div><div class='line' id='LC205'><span class="cm">* len:    the max size of the buf</span></div><div class='line' id='LC206'><span class="cm">* return: num of the bytes read from uart, or -1 if error</span></div><div class='line' id='LC207'><span class="cm">***********************************************************</span></div><div class='line' id='LC208'><span class="cm">*/</span></div><div class='line' id='LC209'><span class="kt">int</span> <span class="nf">read_uart</span><span class="p">(</span><span class="kt">int</span> <span class="n">fd</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">char</span> <span class="o">*</span><span class="n">buf</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">len</span><span class="p">)</span></div><div class='line' id='LC210'><span class="p">{</span></div><div class='line' id='LC211'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">ret</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC212'><br/></div><div class='line' id='LC213'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">fd</span> <span class="o">&lt;</span> <span class="mi">0</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC214'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">perror</span><span class="p">(</span><span class="s">&quot;file description is valid&quot;</span><span class="p">);</span></div><div class='line' id='LC215'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC216'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC217'><br/></div><div class='line' id='LC218'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">buf</span> <span class="o">==</span> <span class="nb">NULL</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC219'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">perror</span><span class="p">(</span><span class="s">&quot;read buf is NULL&quot;</span><span class="p">);</span></div><div class='line' id='LC220'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC221'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span> <span class="k">else</span> <span class="p">{</span></div><div class='line' id='LC222'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">memset</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="n">len</span><span class="p">);</span></div><div class='line' id='LC223'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC224'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC225'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ret</span> <span class="o">=</span> <span class="n">read</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">buf</span><span class="p">,</span> <span class="n">len</span><span class="p">);</span></div><div class='line' id='LC226'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">ret</span> <span class="o">&lt;</span> <span class="mi">0</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC227'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">perror</span><span class="p">(</span><span class="s">&quot;read error:</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC228'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC229'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC230'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC231'><span class="c1">//    if (uart_stat == 0) return -1;</span></div><div class='line' id='LC232'><br/></div><div class='line' id='LC233'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">ret</span><span class="p">;</span></div><div class='line' id='LC234'><span class="p">}</span></div><div class='line' id='LC235'><br/></div><div class='line' id='LC236'><span class="cm">/*</span></div><div class='line' id='LC237'><span class="cm">***********************************************************</span></div><div class='line' id='LC238'><span class="cm">* write_uart</span></div><div class='line' id='LC239'><span class="cm">* send bytes to uart</span></div><div class='line' id='LC240'><span class="cm">* fd:     uart file description</span></div><div class='line' id='LC241'><span class="cm">* buf:    bytes in which will be sent</span></div><div class='line' id='LC242'><span class="cm">* len:    the num of the bytes to be sent</span></div><div class='line' id='LC243'><span class="cm">* return: the num sent to the write buf, or -1 if error</span></div><div class='line' id='LC244'><span class="cm">***********************************************************</span></div><div class='line' id='LC245'><span class="cm">*/</span></div><div class='line' id='LC246'><span class="kt">int</span> <span class="nf">write_uart</span><span class="p">(</span><span class="kt">int</span> <span class="n">fd</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">char</span> <span class="o">*</span><span class="n">buf</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">len</span><span class="p">)</span></div><div class='line' id='LC247'><span class="p">{</span></div><div class='line' id='LC248'>	<span class="kt">int</span> <span class="n">ret</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC249'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">i</span><span class="p">;</span></div><div class='line' id='LC250'><br/></div><div class='line' id='LC251'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">for</span> <span class="p">(</span><span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">len</span><span class="p">;</span> <span class="n">i</span> <span class="o">++</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC252'>	    <span class="k">while</span><span class="p">(</span><span class="n">tcdrain</span><span class="p">(</span><span class="n">fd</span><span class="p">)</span> <span class="o">==</span> <span class="o">-</span><span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC253'>	    <span class="n">ret</span> <span class="o">+=</span> <span class="n">write</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">buf</span><span class="p">[</span><span class="n">i</span><span class="p">],</span> <span class="mi">1</span><span class="p">);</span> </div><div class='line' id='LC254'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC255'><br/></div><div class='line' id='LC256'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">ret</span> <span class="o">&lt;</span> <span class="mi">0</span><span class="p">)</span> <span class="n">perror</span><span class="p">(</span><span class="s">&quot;write:&quot;</span><span class="p">);</span></div><div class='line' id='LC257'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf_uart</span><span class="p">(</span><span class="n">buf</span><span class="p">,</span> <span class="n">len</span><span class="p">);</span>    </div><div class='line' id='LC258'><br/></div><div class='line' id='LC259'>	<span class="k">return</span> <span class="n">ret</span><span class="p">;</span></div><div class='line' id='LC260'><span class="p">}</span></div><div class='line' id='LC261'><br/></div><div class='line' id='LC262'><span class="cm">/*</span></div><div class='line' id='LC263'><span class="cm">***********************************************************</span></div><div class='line' id='LC264'><span class="cm">* chgb_uart</span></div><div class='line' id='LC265'><span class="cm">* change the opened uart&#39;s baudrate</span></div><div class='line' id='LC266'><span class="cm">* fd: uart file description</span></div><div class='line' id='LC267'><span class="cm">* baud: the baudrate to be changed to</span></div><div class='line' id='LC268'><span class="cm">* return: 0 success, -1 error</span></div><div class='line' id='LC269'><span class="cm">***********************************************************</span></div><div class='line' id='LC270'><span class="cm">*/</span></div><div class='line' id='LC271'><span class="kt">int</span> <span class="nf">chgb_uart</span><span class="p">(</span><span class="kt">int</span> <span class="n">fd</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">baud</span><span class="p">)</span></div><div class='line' id='LC272'><span class="p">{</span></div><div class='line' id='LC273'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int</span> <span class="n">ret</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC274'>	<span class="k">struct</span> <span class="n">termios</span> <span class="n">termios_p</span><span class="p">;</span> </div><div class='line' id='LC275'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">int</span> <span class="n">baudrate</span> <span class="o">=</span> <span class="n">B9600</span><span class="p">;</span></div><div class='line' id='LC276'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC277'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">fd</span> <span class="o">==</span> <span class="o">-</span><span class="mi">1</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC278'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;change_baud error</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC279'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC280'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC281'><br/></div><div class='line' id='LC282'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ret</span> <span class="o">=</span> <span class="n">tcgetattr</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">termios_p</span><span class="p">);</span></div><div class='line' id='LC283'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC284'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">ret</span> <span class="o">==</span> <span class="o">-</span><span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC285'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;tcgetattr error</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">);</span></div><div class='line' id='LC286'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC287'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC288'><br/></div><div class='line' id='LC289'>	<span class="k">switch</span> <span class="p">(</span><span class="n">baud</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC290'>		<span class="k">case</span> <span class="mi">300</span>:</div><div class='line' id='LC291'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B300</span><span class="p">;</span></div><div class='line' id='LC292'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC293'>		<span class="k">case</span> <span class="mi">600</span>:</div><div class='line' id='LC294'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B600</span><span class="p">;</span></div><div class='line' id='LC295'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC296'>		<span class="k">case</span> <span class="mi">1200</span>:</div><div class='line' id='LC297'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B1200</span><span class="p">;</span></div><div class='line' id='LC298'>			<span class="c1">//cfsetispeed(&amp;termios_p, B1200);  </span></div><div class='line' id='LC299'>			<span class="c1">//cfsetospeed(&amp;termios_p, B1200);</span></div><div class='line' id='LC300'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC301'>		<span class="k">case</span> <span class="mi">2400</span>:</div><div class='line' id='LC302'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B2400</span><span class="p">;</span></div><div class='line' id='LC303'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC304'>		<span class="k">case</span> <span class="mi">4800</span>:</div><div class='line' id='LC305'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B4800</span><span class="p">;</span></div><div class='line' id='LC306'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC307'>		<span class="k">case</span> <span class="mi">9600</span>:</div><div class='line' id='LC308'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B9600</span><span class="p">;</span></div><div class='line' id='LC309'>			<span class="c1">//cfsetispeed(&amp;termios_p, B9600);  </span></div><div class='line' id='LC310'>			<span class="c1">//cfsetospeed(&amp;termios_p, B9600); </span></div><div class='line' id='LC311'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC312'>		<span class="k">case</span> <span class="mi">19200</span>:</div><div class='line' id='LC313'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B19200</span><span class="p">;</span></div><div class='line' id='LC314'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC315'>		<span class="k">case</span> <span class="mi">38400</span>:</div><div class='line' id='LC316'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B38400</span><span class="p">;</span></div><div class='line' id='LC317'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC318'>		<span class="k">case</span> <span class="mi">57600</span>:</div><div class='line' id='LC319'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B57600</span><span class="p">;</span></div><div class='line' id='LC320'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC321'>		<span class="k">case</span> <span class="mi">115200</span>:</div><div class='line' id='LC322'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B115200</span><span class="p">;</span></div><div class='line' id='LC323'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC324'>		<span class="nl">default:</span></div><div class='line' id='LC325'>			<span class="n">baudrate</span> <span class="o">=</span>  <span class="n">B9600</span><span class="p">;</span></div><div class='line' id='LC326'>			<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC327'>	<span class="p">}</span></div><div class='line' id='LC328'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">cfsetispeed</span><span class="p">(</span><span class="o">&amp;</span><span class="n">termios_p</span><span class="p">,</span> <span class="n">baudrate</span><span class="p">);</span>  </div><div class='line' id='LC329'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">cfsetospeed</span><span class="p">(</span><span class="o">&amp;</span><span class="n">termios_p</span><span class="p">,</span> <span class="n">baudrate</span><span class="p">);</span></div><div class='line' id='LC330'><br/></div><div class='line' id='LC331'><br/></div><div class='line' id='LC332'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span><span class="p">(</span><span class="n">tcdrain</span><span class="p">(</span><span class="n">fd</span><span class="p">)</span> <span class="o">==</span> <span class="o">-</span><span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC333'><br/></div><div class='line' id='LC334'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">tcflush</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">TCOFLUSH</span><span class="p">);</span>  </div><div class='line' id='LC335'>	<span class="n">tcflush</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">TCIFLUSH</span><span class="p">);</span></div><div class='line' id='LC336'><br/></div><div class='line' id='LC337'><br/></div><div class='line' id='LC338'>	<span class="n">tcsetattr</span><span class="p">(</span><span class="n">fd</span><span class="p">,</span> <span class="n">TCSANOW</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">termios_p</span><span class="p">);</span></div><div class='line' id='LC339'><br/></div><div class='line' id='LC340'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;Baudrate is %d</span><span class="se">\n\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="n">baud</span><span class="p">);</span></div><div class='line' id='LC341'>&nbsp;&nbsp;&nbsp;&nbsp;</div><div class='line' id='LC342'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC343'><br/></div><div class='line' id='LC344'><span class="p">}</span></div></pre></div></td>
          </tr>
        </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github" title="GitHub"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2014 <span title="0.07218s from github-fe123-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="fullscreen-contents js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped tooltipped-w" aria-label="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped tooltipped-w"
      aria-label="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-remove-close close js-ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>

  </body>
</html>

