INSTALL_DIR:=/usr/local/bin

pi:
	@zig cc -I include src/**/*.c src/pi.c -o pi

.PHONY: install
install: pi
	install -m 755 pi ${INSTALL_DIR}

.PHONY: release
release:
	@zig cc -I include src/**/*.c src/pi.c -o pi_windows_x86-64.exe -target x86_64-windows-gnu -O3
	@zig cc -I include src/**/*.c src/pi.c -o pi_linux_x86-64_gnu -target x86_64-linux-gnu -O3
	@zig cc -I include src/**/*.c src/pi.c -o pi_linux_x86-64_musl -target x86_64-linux-musl -O3

.PHONY: clean
clean:
	@rm -f pi
	@rm -f pi*_windows_x86-64.exe
	@rm -f pi*_linux_x86-64_gnu
	@rm -f pi*_linux_x86-64_musl
