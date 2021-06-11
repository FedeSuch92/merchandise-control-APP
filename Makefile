.PHONY: clean All

All:
	@echo "----------Building project:[ UOCTransport - Menu ]----------"
	@"$(MAKE)" -f  "UOCTransport.mk"
clean:
	@echo "----------Cleaning project:[ UOCTransport - Menu ]----------"
	@"$(MAKE)" -f  "UOCTransport.mk" clean
