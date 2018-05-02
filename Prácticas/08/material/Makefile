compile:
	gcc mm-ijk.c tiempo.c -DN=6 -o IJK-EXE6.elf
	gcc mm-jki.c tiempo.c -DN=6 -o JKI-EXE6.elf
	gcc mm-kij.c tiempo.c -DN=6 -o KIJ-EXE6.elf

	gcc mm-ijk.c tiempo.c -DN=256 -o IJK-EXE256.elf
	gcc mm-jki.c tiempo.c -DN=256 -o JKI-EXE256.elf
	gcc mm-kij.c tiempo.c -DN=256 -o KIJ-EXE256.elf

	gcc mm-ijk.c tiempo.c -DN=512 -o IJK-EXE512.elf
	gcc mm-jki.c tiempo.c -DN=512 -o JKI-EXE512.elf
	gcc mm-kij.c tiempo.c -DN=512 -o KIJ-EXE512.elf

	gcc mm-ijk.c tiempo.c -DN=1024 -o IJK-EXE1024.elf
	gcc mm-jki.c tiempo.c -DN=1024 -o JKI-EXE1024.elf
	gcc mm-kij.c tiempo.c -DN=1024 -o KIJ-EXE1024.elf



	gcc mm-ijk2.c tiempo.c -DN=6 -o IJK2-EXE6.elf
	gcc mm-jki2.c tiempo.c -DN=6 -o JKI2-EXE6.elf
	gcc mm-kij2.c tiempo.c -DN=6 -o KIJ2-EXE6.elf

	gcc mm-ijk2.c tiempo.c -DN=256 -o IJK2-EXE256.elf
	gcc mm-jki2.c tiempo.c -DN=256 -o JKI2-EXE256.elf
	gcc mm-kij2.c tiempo.c -DN=256 -o KIJ2-EXE256.elf

	gcc mm-ijk2.c tiempo.c -DN=512 -o IJK2-EXE512.elf
	gcc mm-jki2.c tiempo.c -DN=512 -o JKI2-EXE512.elf
	gcc mm-kij2.c tiempo.c -DN=512 -o KIJ2-EXE512.elf

	gcc mm-ijk2.c tiempo.c -DN=1024 -o IJK2-EXE1024.elf
	gcc mm-jki2.c tiempo.c -DN=1024 -o JKI2-EXE1024.elf
	gcc mm-kij2.c tiempo.c -DN=1024 -o KIJ2-EXE1024.elf


run:
	./IJK-EXE6.elf > 2_t_6_ijk.txt
	./JKI-EXE6.elf > 2_t_6_jki.txt
	./KIJ-EXE6.elf > 2_t_6_kij.txt
 
	./IJK-EXE256.elf > 2_t_256_ikj.txt
	./JKI-EXE256.elf > 2_t_256_jki.txt
	./KIJ-EXE256.elf > 2_t_256_kij.txt

	./IJK-EXE512.elf > 2_t_512_ijk.txt
	./JKI-EXE512.elf > 2_t_512_jki.txt
	./KIJ-EXE512.elf > 2_t_512_kij.txt
 
	./IJK-EXE1024.elf > 2_t_1024_ijk.txt
	./JKI-EXE1024.elf > 2_t_1024_jki.txt
	./KIJ-EXE1024.elf > 2_t_1024_kij.txt



	./IJK2-EXE6.elf > 5_t_6_ijk.txt
	./JKI2-EXE6.elf > 5_t_6_jki.txt
	./KIJ2-EXE6.elf > 5_t_6_kij.txt
 
	./IJK2-EXE256.elf > 5_t_256_ikj.txt
	./JKI2-EXE256.elf > 5_t_256_jki.txt
	./KIJ2-EXE256.elf > 5_t_256_kij.txt

	./IJK2-EXE512.elf > 5_t_512_ijk.txt
	./JKI2-EXE512.elf > 5_t_512_jki.txt
	./KIJ2-EXE512.elf > 5_t_512_kij.txt
 
	./IJK2-EXE1024.elf > 5_t_1024_ijk.txt
	./JKI2-EXE1024.elf > 5_t_1024_jki.txt
	./KIJ2-EXE1024.elf > 5_t_1024_kij.txt
	
calculate:
	py MFlops.py


clear:
	rm *.elf

