ESDK = $(EPIPHANY_HOME)
ELIBS = $(ESDK)/tools/host/lib
EINCS = $(ESDK)/tools/host/include
ELDF = $(ESDK)/bsps/current/internal.ldf

HC = gcc
DC = e-gcc

HOST_FLAGS = -I $(EINCS) -L $(ELIBS) -le-hal -le-loader
DEVICE_FLAGS = -O2 -T $(ELDF) -le-lib -lm 


all: host device 

host: host_main.elf

device: e_task.elf

host_main.elf: ./src/h_main.c
	$(HC) $< -o ./build/$@ $(HOST_FLAGS)

e_task.elf: ./src/e_task.c
	$(DC) -O3  -T $(ELDF) $< -o ./build/$@ -le-lib -lm 

clean:
	rm ./build/host_main.elf && rm ./build/e_task.elf
