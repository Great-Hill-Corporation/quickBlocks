## getTrans

The `getTrans` tool retrieves transactions from the running Ethereum node (using the `--raw` option) or from QuickBlocks (the default). You may provide a transaction `hash`, a `blockNumber.transactionID` pair, or a `blockHash.transactionID` pair (or any combination) to specify the transaction(s).

Use the `--trace` option to display a trace of the transaction as well.

#### Usage

`Usage:`    getTrans [-r|-v|-h] &lt;transID&gt; [transID...]  
`Purpose:`  Retrieve an Ethereum transaction from the local cache or a running node.  
`Where:`  

| Short Cut | Option | Description |
| -------: | :------- | :------- |
|  | trans_list | a space-separated list of one or more transaction identifiers (tx_hash, bn.txID, blk_hash.txID) |
| -r | --raw | retrieve raw transaction directly from the running node |
| -v | --verbose | set verbose level. Either -v, --verbose or -v:n where 'n' is level |
| -h | --help | display this help screen |

`Notes:`

- `trans_list` is one or more space-separated identifiers which may be either a transaction hash,
  a blockNumber.transactionID pair, or a blockHash.transactionID pair, or any combination.
- This tool checks for valid input syntax, but does not check that the transaction requested exists.
- This tool retrieves information from the local node or the ${FALLBACK} node, if configured (see documentation).
- If the queried node does not store historical state, the results may be undefined.

*See Also*: This command-line tool implements these RPC interfaces:
[eth_getTransactionByHash](https://github.com/paritytech/parity/wiki/JSONRPC-eth-module#eth_gettransactionbyhash), 
[eth_getTransactionByBlockNumberAndIndex](https://github.com/paritytech/parity/wiki/JSONRPC-eth-module#eth_gettransactionbyblocknumberandindex),
[eth_getTransactionByBlockHashAndIndex](https://github.com/paritytech/parity/wiki/JSONRPC-eth-module#eth_gettransactionbyblockhashandindex).

#### Other Options

All **quickBlocks** command-line tools support the following commands (although in some case, they have no meaning):

    Command     |     Description
    -----------------------------------------------------------------------------
    --version   |   display the current version of the tool
    --nocolor   |   turn off colored display
    --wei       |   specify value in wei (the default)
    --ether     |   specify value in ether
    --dollars   |   specify value in US dollars
    --file:fn   |   specify multiple sets of command line options in a file.

<small>*For the `--file:fn` option, place a series of valid command lines in a file and use the above options. In some cases, this option may significantly improve performance. A semi-colon at the start of a line makes that line a comment.*</small>

**Powered by QuickBlocks<sup>&reg;</sup>**


