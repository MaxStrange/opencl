## OpenCL directory:
This is my own implementation of OpenCL for the Epiphany device. To use it,
run `make` in this directory and take the resulting .so file and place it in the
/usr/local/OpenCL/vendors/max/ directory (which isn't there, so you need to make
it). Then add a file to /etc/OpenCL/vendors/ called `max.icd` that has a single
line in it: `/usr/local/OpenCL/vendors/max/libeocl.so`

You may need to alter your path as well... Not sure yet.
