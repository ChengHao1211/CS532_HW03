mySearch: yuc_HW3.c
	gcc -Wall -o search yuc_HW3.c
	mkdir project
	mkdir project1
	mv project1 project
	touch README
	mv README project/project1
	touch project1.docx
	mv project1.docx project/project1

	mkdir project2
	mv project2 project
	touch README
	mv README project/project2
	touch project2.docx
	mv project2.docx project/project2


	mkdir project3
	mv project3 project
	touch README
	mv README project/project3
	touch project3.docx
	mv project3.docx project/project3


	mkdir project4
	mv project4 project
	touch README
	mv README project/project4
	touch project4.docx
	mv project4.docx project/project4

rmfile:
	rm project/project1/project1.docx
	rm project/project1/README
	rmdir project/project1/
	rm project/project2/project2.docx
	rm project/project2/README
	rmdir project/project2/
	rm project/project3/project3.docx
	rm project/project3/README
	rmdir project/project3/
	rm project/project4/project4.docx
	rm project/project4/README
	rmdir project/project4/
	rmdir project/

