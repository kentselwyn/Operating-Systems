CC = sdcc
CFLAGS = -c --model-small
LDFLAGS = 
OBJ = preemptive.rel lcdlib.rel buttonlib.rel keylib.rel

# @@@ substitute the following recepe into `all: testlcd.hex dino.hex` when you are doing part 2 of this checkpoint
all: testlcd.hex dino.hex

testlcd.hex: testlcd.rel $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $< $(OBJ)

dino.hex: dino.rel $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $< $(OBJ)

%.rel: %.c preemptive.h Makefile
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.hex *.ihx *.lnk *.lst *.map *.mem *.rel *.rst *.sym *.asm *.lk
