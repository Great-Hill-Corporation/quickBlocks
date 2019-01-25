## whereBlock

`whereBlock` reports on the location of a block (or blocks) in the cache. It reports on one of four situations: `cache`, `node` or `none` depending on where the block is found.

If `whereBlock` finds the block in the QBlocks cache, it reports the path to that block's file. If the block is not in the cache, but there is a locally running node, `whereBlock` returns `node` plus the name and version info from the running node. Otherwise, `whereBlock` returns `none`.

This tool is intended mostly as an aid in developing and debugging QBlocks tools.

#### Usage

`Usage:`    whereBlock [-a|-b|-v|-h] &lt;block&gt; [block...]  
`Purpose:`  Reports if a block was found in the cache, at a local, or at a remote node.
             
`Where:`  

| Short Cut | Option | Description |
| -------: | :------- | :------- |
|  | block_list | a space-separated list of one or more blocks to search for |
| -a | --account | find an account file, not the block file |
| -b | --bloom | find a bloom file, not the block file |
| -v | --verbose | set verbose level. Either -v, --verbose or -v:n where 'n' is level |
| -h | --help | display this help screen |

#### Other Options

All **QBlocks** command-line tools support the following commands (although in some case, they have no meaning):

    Command     |     Description
    -----------------------------------------------------------------------------
    --version   |   display the current version of the tool
    --nocolor   |   turn off colored display
    --wei       |   specify value in wei (the default)
    --ether     |   specify value in ether
    --dollars   |   specify value in US dollars
    --file:fn   |   specify multiple sets of command line options in a file.

<small>*For the `--file:fn` option, place a series of valid command lines in a file and use the above options. In some cases, this option may significantly improve performance. A semi-colon at the start of a line makes that line a comment.*</small>

**Powered by Qblocks<sup>&trade;</sup>**


