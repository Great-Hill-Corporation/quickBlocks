/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include "acctlib.h"
#include "options.h"

//------------------------------------------------------------------------------------------------------------
extern const char* STR_THE_FILE;
bool COptions::handle_js(void) {
    cout << STR_THE_FILE << endl;
    return true;
}

const char* STR_THE_FILE =
    "import React from 'react';\n"
    "import { Route, Switch } from 'react-router-dom';\n"
    "import { DashboardView, ExplorerView, NamesView, SettingsView, SupportView } from './views';\n"
    "\n"
    "export const RootLocation = '/';\n"
    "export const DashboardLocation = '/dashboard';\n"
    "export const DashboardMonitorsLocation = '/dashboard/monitors';\n"
    "export const DashboardAccountsLocation = '/dashboard/accounts';\n"
    "export const DashboardAccountsAddressLocationTemplate = '/dashboard/accounts/:address';\n"
    "export const DashboardAccountsAddressLocation = (address: string) => `/dashboard/accounts/${address}`;\n"
    "export const AccountReconsLocation = '/dashboard/accounts/recons';\n"
    "export const AccountReconsLocationAddressTemplate = '/dashboard/accounts/recons/:address';\n"
    "export const AccountReconsLocationAddress = (address: string) => `/dashboard/accounts/recons/${address}`;\n"
    "export const AccountFunctionsLocation = '/dashboard/accounts/functions';\n"
    "export const AccountFunctionsLocationAddressTemplate = '/dashboard/accounts/functions/:address';\n"
    "export const AccountFunctionsLocationAddress = (address: string) => `/dashboard/accounts/functions/${address}`;\n"
    "export const AccountGasLocation = '/dashboard/accounts/gas';\n"
    "export const AccountGasLocationAddressTemplate = '/dashboard/accounts/gas/:address';\n"
    "export const AccountGasLocationAddress = (address: string) => `/dashboard/accounts/gas/${address}`;\n"
    "export const AccountTracesLocation = '/dashboard/accounts/traces';\n"
    "export const AccountTracesLocationAddressTemplate = '/dashboard/accounts/traces/:address';\n"
    "export const AccountTracesLocationAddress = (address: string) => `/dashboard/accounts/traces/${address}`;\n"
    "export const AccountRawLocation = '/dashboard/accounts/raw';\n"
    "export const AccountRawLocationAddressTemplate = '/dashboard/accounts/raw/:address';\n"
    "export const AccountRawLocationAddress = (address: string) => `/dashboard/accounts/raw/${address}`;\n"
    "export const DashboardCollectionsLocation = '/dashboard/collections';\n"
    "export const NamesLocation = '/names';\n"
    "export const NamesAddressesLocation = '/names/addresses';\n"
    "export const NamesTagsLocation = '/names/tags';\n"
    "export const NamesFuncSigsLocation = '/names/funcsigs';\n"
    "export const NamesEventSigsLocation = '/names/eventsigs';\n"
    "export const NamesBlocksLocation = '/names/blocks';\n"
    "export const ExplorerLocation = '/explorer';\n"
    "export const ExplorerBlocksLocation = '/explorer/blocks';\n"
    "export const ExplorerTransactionsLocation = '/explorer/transactions';\n"
    "export const ExplorerReceiptsLocation = '/explorer/receipts';\n"
    "export const ExplorerLogsLocation = '/explorer/logs';\n"
    "export const ExplorerTracesLocation = '/explorer/traces';\n"
    "export const SettingsLocation = '/settings';\n"
    "export const SettingsScrapersLocation = '/settings/scrapers';\n"
    "export const SettingsIndexesLocation = '/settings/indexes';\n"
    "export const SettingsIndexGridLocation = '/settings/indexes/grid';\n"
    "export const SettingsIndexTableLocation = '/settings/indexes/table';\n"
    "export const SettingsIndexChartsLocation = '/settings/indexes/charts';\n"
    "export const SettingsIndexManifestLocation = '/settings/indexes/manifest';\n"
    "export const SettingsCachesLocation = '/settings/caches';\n"
    "export const SettingsSkinsLocation = '/settings/skins';\n"
    "export const SettingsSchemasLocation = '/settings/schemas';\n"
    "export const SupportLocation = '/support';\n"
    "export const SupportContactUsLocation = '/support/contact-us';\n"
    "export const SupportDocumentationLocation = '/support/documentation';\n"
    "export const SupportHotKeysLocation = '/support/hot-keys';\n"
    "export const SupportLicensingLocation = '/support/licensing';\n"
    "export const SupportAboutUsLocation = '/support/about-us';\n"
    "\n"
    "const routes = [\n"
    "  {\n"
    "    path: RootLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: DashboardLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: DashboardAccountsLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: DashboardAccountsAddressLocationTemplate,\n"
    "    exact: false,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountFunctionsLocationAddressTemplate,\n"
    "    exact: false,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountGasLocationAddressTemplate,\n"
    "    exact: false,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountTracesLocationAddressTemplate,\n"
    "    exact: false,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountReconsLocationAddressTemplate,\n"
    "    exact: false,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountFunctionsLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountGasLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountRawLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountTracesLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: AccountReconsLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: DashboardMonitorsLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: DashboardCollectionsLocation,\n"
    "    exact: true,\n"
    "    component: DashboardView,\n"
    "  },\n"
    "  {\n"
    "    path: NamesLocation,\n"
    "    exact: true,\n"
    "    component: NamesView,\n"
    "  },\n"
    "  {\n"
    "    path: NamesAddressesLocation,\n"
    "    exact: true,\n"
    "    component: NamesView,\n"
    "  },\n"
    "  {\n"
    "    path: NamesTagsLocation,\n"
    "    exact: true,\n"
    "    component: NamesView,\n"
    "  },\n"
    "  {\n"
    "    path: NamesFuncSigsLocation,\n"
    "    exact: true,\n"
    "    component: NamesView,\n"
    "  },\n"
    "  {\n"
    "    path: NamesEventSigsLocation,\n"
    "    exact: true,\n"
    "    component: NamesView,\n"
    "  },\n"
    "  {\n"
    "    path: NamesBlocksLocation,\n"
    "    exact: true,\n"
    "    component: NamesView,\n"
    "  },\n"
    "  {\n"
    "    path: ExplorerLocation,\n"
    "    exact: true,\n"
    "    component: ExplorerView,\n"
    "  },\n"
    "  {\n"
    "    path: ExplorerBlocksLocation,\n"
    "    exact: true,\n"
    "    component: ExplorerView,\n"
    "  },\n"
    "  {\n"
    "    path: ExplorerTransactionsLocation,\n"
    "    exact: true,\n"
    "    component: ExplorerView,\n"
    "  },\n"
    "  {\n"
    "    path: ExplorerReceiptsLocation,\n"
    "    exact: true,\n"
    "    component: ExplorerView,\n"
    "  },\n"
    "  {\n"
    "    path: ExplorerLogsLocation,\n"
    "    exact: true,\n"
    "    component: ExplorerView,\n"
    "  },\n"
    "  {\n"
    "    path: ExplorerTracesLocation,\n"
    "    exact: true,\n"
    "    component: ExplorerView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsScrapersLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsIndexesLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsIndexGridLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsIndexTableLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsIndexChartsLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsIndexManifestLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsCachesLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsSkinsLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SettingsSchemasLocation,\n"
    "    exact: true,\n"
    "    component: SettingsView,\n"
    "  },\n"
    "  {\n"
    "    path: SupportLocation,\n"
    "    exact: true,\n"
    "    component: SupportView,\n"
    "  },\n"
    "  {\n"
    "    path: SupportContactUsLocation,\n"
    "    exact: true,\n"
    "    component: SupportView,\n"
    "  },\n"
    "  {\n"
    "    path: SupportDocumentationLocation,\n"
    "    exact: true,\n"
    "    component: SupportView,\n"
    "  },\n"
    "  {\n"
    "    path: SupportHotKeysLocation,\n"
    "    exact: true,\n"
    "    component: SupportView,\n"
    "  },\n"
    "  {\n"
    "    path: SupportLicensingLocation,\n"
    "    exact: true,\n"
    "    component: SupportView,\n"
    "  },\n"
    "  {\n"
    "    path: SupportAboutUsLocation,\n"
    "    exact: true,\n"
    "    component: SupportView,\n"
    "  },\n"
    "];\n"
    "\n"
    "const CustomRoute = (props: any) => {\n"
    "  const { path, component, exact } = props;\n"
    "  return <Route path={path} component={component} exact={exact} />;\n"
    "};\n"
    "\n"
    "export const Routes = () => (\n"
    "  <Switch>\n"
    "    {routes.map((props) => (\n"
    "      <CustomRoute key={props.path} {...props} />\n"
    "    ))}\n"
    "    <DashboardView />\n"
    "  </Switch>\n"
    ");\n"
    "\n"
    "export const helpRoutes = [\n"
    "  {\n"
    "    route: RootLocation,\n"
    "    helpText: 'The dashboard overview page gives you an overview of your holdings among other things.',\n"
    "  },\n"
    "  {\n"
    "    route: DashboardLocation,\n"
    "    helpText: 'The dashboard overview page gives you an overview of your holdings among other things.',\n"
    "  },\n"
    "  {\n"
    "    route: DashboardAccountsLocation,\n"
    "    helpText: 'View the transactional history of an account.',\n"
    "  },\n"
    "  {\n"
    "    route: AccountRawLocation,\n"
    "    helpText: 'View the raw transaction.',\n"
    "  },\n"
    "  {\n"
    "    route: AccountTracesLocation,\n"
    "    helpText: 'View the history of traces for the transaction.',\n"
    "  },\n"
    "  {\n"
    "    route: AccountGasLocation,\n"
    "    helpText: 'View the event history of an account.',\n"
    "  },\n"
    "  {\n"
    "    route: AccountReconsLocation,\n"
    "    helpText: 'View the reconciliation history of an account.',\n"
    "  },\n"
    "  {\n"
    "    route: AccountFunctionsLocation,\n"
    "    helpText: 'View the functional history of an account.',\n"
    "  },\n"
    "  {\n"
    "    route: DashboardMonitorsLocation,\n"
    "    helpText:\n"
    "      'Monitors are named addresses that you have indicated are of interest and should be monitored by the "
    "scrapers.',\n"
    "  },\n"
    "  {\n"
    "    route: DashboardCollectionsLocation,\n"
    "    helpText: 'Collections allow you to group together multiple monitored addresses.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsIndexesLocation,\n"
    "    helpText: (\n"
    "      <div>\n"
    "        <p>View the contents of the TrueBlocks index cache.</p>\n"
    "        <p>\n"
    "          For more information on the process of extracting the index,\n"
    "          <a target='_blank' href='https://github.com/TrueBlocks/trueblocks-docs/issues/12'>\n"
    "            see here\n"
    "          </a>\n"
    "          .\n"
    "        </p>\n"
    "      </div>\n"
    "    ),\n"
    "  },\n"
    "  {\n"
    "    route: SettingsIndexChartsLocation,\n"
    "    helpText: 'Charts related to the index cache.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsIndexManifestLocation,\n"
    "    helpText: 'Charts related to the index cache.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsIndexGridLocation,\n"
    "    helpText: 'Grid view of the index cache.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsIndexTableLocation,\n"
    "    helpText: 'Table view of the index cache.',\n"
    "  },\n"
    "  {\n"
    "    route: NamesLocation,\n"
    "    helpText: 'Names are common or known addresses that have been given a name.',\n"
    "  },\n"
    "  {\n"
    "    route: NamesAddressesLocation,\n"
    "    helpText: 'Named addresses are a convenient way to keep track of human-readable names for addresses.',\n"
    "  },\n"
    "  {\n"
    "    route: NamesTagsLocation,\n"
    "    helpText: 'Tags are groupings used to collect together named addresses.',\n"
    "  },\n"
    "  {\n"
    "    route: NamesFuncSigsLocation,\n"
    "    helpText: 'The function signatures tab allows you to add/edit/delete four byte signatures.',\n"
    "  },\n"
    "  {\n"
    "    route: NamesEventSigsLocation,\n"
    "    helpText: 'The event signatures tab allows you to add/edit/delete event signatures.',\n"
    "  },\n"
    "  {\n"
    "    route: NamesBlocksLocation,\n"
    "    helpText:\n"
    "      'The blocks tab allows you to name particular blocks such as notable smart contract deployments, hard "
    "forks, or other blocks.',\n"
    "  },\n"
    "  {\n"
    "    route: ExplorerLocation,\n"
    "    helpText: 'View the contents of the TrueBlocks index cache.',\n"
    "  },\n"
    "  {\n"
    "    route: ExplorerBlocksLocation,\n"
    "    helpText: 'View blockchain block details.',\n"
    "  },\n"
    "  {\n"
    "    route: ExplorerTransactionsLocation,\n"
    "    helpText: 'View blockchain transaction details.',\n"
    "  },\n"
    "  {\n"
    "    route: ExplorerReceiptsLocation,\n"
    "    helpText: 'View blockchain receipt details.',\n"
    "  },\n"
    "  {\n"
    "    route: ExplorerLogsLocation,\n"
    "    helpText: 'View blockchain log details.',\n"
    "  },\n"
    "  {\n"
    "    route: ExplorerTracesLocation,\n"
    "    helpText: 'View blockchain trace details.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsLocation,\n"
    "    helpText: 'This screen allows you to adjust the way TrueBlocks two scrapers work.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsScrapersLocation,\n"
    "    helpText: 'This screen allows you to adjust the way TrueBlocks two scrapers work.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsCachesLocation,\n"
    "    helpText: 'View, edit, clean, recover space from the TrueBlocks caches.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsSkinsLocation,\n"
    "    helpText: 'Change the skin or them of the application.',\n"
    "  },\n"
    "  {\n"
    "    route: SettingsSchemasLocation,\n"
    "    helpText: 'View and edit the schemas for the various screens and tables.',\n"
    "  },\n"
    "  {\n"
    "    route: SupportLocation,\n"
    "    helpText: 'Information on contacting TrueBlocks, LLC.',\n"
    "  },\n"
    "  {\n"
    "    route: SupportContactUsLocation,\n"
    "    helpText: 'Information on contacting TrueBlocks, LLC.',\n"
    "  },\n"
    "  {\n"
    "    route: SupportDocumentationLocation,\n"
    "    helpText: 'Links to various documentation sites.',\n"
    "  },\n"
    "  {\n"
    "    route: SupportHotKeysLocation,\n"
    "    helpText: 'A view of all the hot-keys for the program.',\n"
    "  },\n"
    "  {\n"
    "    route: SupportLicensingLocation,\n"
    "    helpText: 'Licensing information about the software.',\n"
    "  },\n"
    "  {\n"
    "    route: SupportAboutUsLocation,\n"
    "    helpText: 'A short history of TrueBlocks, LLC.',\n"
    "  },\n"
    "];";