## [{NAME}]

`whereBlock` reports on the location of a block (or blocks) in the cache. It reports on one of four situations: `cache`, `node` or `none` depending on where the block is found.

If `whereBlock` finds the block in the QBlocks cache, it reports the path to that block's file. If the block is not in the cache, but there is a locally running node, `whereBlock` returns `node` plus the name and version info from the running node. Otherwise, `whereBlock` returns `none`.

This tool is intended mostly as an aid in developing and debugging QBlocks tools.

[{USAGE_TABLE}][{FOOTER}]
