ordonnancement : ordonnancement.c ordonnancement.h main.c 
				gcc -o ordonnancement main.c ordonnancement.c
run: ordonnancement
		./ordonnancement
		 
clean: 
		rm ordonnancement		

