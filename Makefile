install:
	gcc -o rb main.c
	echo "Moving rb into /usr/bin/"
	sudo mv rb /usr/bin/

	echo "file /usr/bin/rb created."
	echo "All done."