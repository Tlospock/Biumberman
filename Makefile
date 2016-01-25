.PHONY: clean All

All:
	@echo "----------Building project:[ biumberman - Debug ]----------"
	@"$(MAKE)" -f  "biumberman.mk"
clean:
	@echo "----------Cleaning project:[ biumberman - Debug ]----------"
	@"$(MAKE)" -f  "biumberman.mk" clean
