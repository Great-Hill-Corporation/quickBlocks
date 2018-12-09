# Deploy basic configuration and directories structure for quickblocks

set(QUICKBLOCKS_HOME "$ENV{HOME}/.quickBlocks")

# create the files (will silently fail if already present)
message(STATUS "Establishing configuration folders at ${QUICKBLOCKS_HOME}")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/names")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/cache")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/cache/abis")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/cache/prices")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/cache/tmp")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/known_abis")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/makeClass")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/grabABI")
file(MAKE_DIRECTORY "${QUICKBLOCKS_HOME}/chifra")

# Create toml file only if it does not exist
set(QUICKBLOCKS_TOML_FILE "${QUICKBLOCKS_HOME}/quickBlocks.toml")
if (NOT EXISTS "${QUICKBLOCKS_TOML_FILE}")
    message(STATUS "Copying configuration files ${QUICKBLOCKS_TOML_FILE}")
    file(COPY "${CMAKE_SOURCE_DIR}/../../../src/other/install/quickBlocks.toml" DESTINATION "${QUICKBLOCKS_HOME}" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)
endif()

# Create toml file only if it does not exist
set(QUICKBLOCKS_TOML_FILE "${QUICKBLOCKS_HOME}/whenBlock.toml")
if (NOT EXISTS "${QUICKBLOCKS_TOML_FILE}")
    message(STATUS "Copying custom configuration file ${QUICKBLOCKS_TOML_FILE}")
    file(COPY "${CMAKE_SOURCE_DIR}/../../../src/other/install/whenBlock.toml" DESTINATION "${QUICKBLOCKS_HOME}" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)
endif()

# Create toml file only if it does not exist
set(QUICKBLOCKS_TOML_FILE "${QUICKBLOCKS_HOME}/ethslurp.toml")
if (NOT EXISTS "${QUICKBLOCKS_TOML_FILE}")
    message(STATUS "Copying custom configuration file ${QUICKBLOCKS_TOML_FILE}")
    file(COPY "${CMAKE_SOURCE_DIR}/../../../src/other/install/ethslurp.toml" DESTINATION "${QUICKBLOCKS_HOME}" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)
endif()

# Create names file only if it does not exist
set(QUICKBLOCKS_NAMES_FILE "${QUICKBLOCKS_HOME}/names/names.txt")
if (NOT EXISTS "${QUICKBLOCKS_NAMES_FILE}")
    message(STATUS "Copying names file ${QUICKBLOCKS_NAMES_FILE}")
    file(COPY "${CMAKE_SOURCE_DIR}/../../../src/other/install/names.txt" DESTINATION "${QUICKBLOCKS_HOME}/names" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)
endif()

# Create names file only if it does not exist
set(QUICKBLOCKS_PRICES_FILE "${QUICKBLOCKS_HOME}/cache/prices/poloniex_USDT_ETH.bin.gz")
if (NOT EXISTS "${QUICKBLOCKS_PRICES_FILE}")
    set(QUICKBLOCKS_PRICES_SOURCE "${CMAKE_SOURCE_DIR}/../../../src/other/install/prices/poloniex_USDT_ETH.bin.gz")
    message(STATUS "Copying price data to ${QUICKBLOCKS_HOME}/cache/prices")
    file(COPY "${QUICKBLOCKS_PRICES_SOURCE}" DESTINATION "${QUICKBLOCKS_HOME}/cache/prices" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)
endif()

# prefund
message(STATUS "Copying prefund file ${QUICKBLOCKS_HOME}/prefunds.txt")
file(COPY "${CMAKE_SOURCE_DIR}/../../../src/other/install/prefunds.txt" DESTINATION "${QUICKBLOCKS_HOME}/" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)

# makeClass content
file(COPY "${CMAKE_SOURCE_DIR}/../../../bin/makeClass" DESTINATION "${QUICKBLOCKS_HOME}/makeClass")
file(GLOB TARGET_FILES "${CMAKE_SOURCE_DIR}/../../../src/apps/makeClass/templates/blank*")
foreach(FILE ${TARGET_FILES} )
	file(COPY "${FILE}" DESTINATION "${QUICKBLOCKS_HOME}/makeClass")
endforeach( FILE )

# grabABI content
file(GLOB TARGET_FILES "${CMAKE_SOURCE_DIR}/../../../src/apps/grabABI/templates/*")
foreach(FILE ${TARGET_FILES} )
	file(COPY "${FILE}" DESTINATION "${QUICKBLOCKS_HOME}/grabABI")
endforeach( FILE )

# chifra content
file(GLOB TARGET_FILES "${CMAKE_SOURCE_DIR}/../../../src/apps/chifra/templates/*")
foreach(FILE ${TARGET_FILES} )
      file(COPY "${FILE}" DESTINATION "${QUICKBLOCKS_HOME}/chifra")
endforeach( FILE )

# known abis
file(GLOB TARGET_FILES "${CMAKE_SOURCE_DIR}/../../../src/other/install/known_abis/*")
foreach(FILE ${TARGET_FILES} )
      file(COPY "${FILE}" DESTINATION "${QUICKBLOCKS_HOME}/known_abis")
endforeach( FILE )
