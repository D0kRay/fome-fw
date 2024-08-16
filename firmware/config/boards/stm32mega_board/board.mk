# List of all the board related files.
BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp

# Override DEFAULT_ENGINE_TYPE
SHORT_BOARD_NAME = stm32mega
DDEFS += -DFIRMWARE_ID=\"stm32mega\"
DDEFS += -DDEFAULT_ENGINE_TYPE=MINIMAL_PINS
DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE -DSTM32_ADC_USE_ADC3=TRUE
