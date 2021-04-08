mytest:mytest.c
	gcc -o $@ $^ -I ./mylib/include -L ./mylib/lib -l mymath -static 
.PHONY:clean
clean:
	rm mytest
