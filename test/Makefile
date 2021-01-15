all :
	gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 ../mandatory/get_next_line.c ../mandatory/get_next_line_utils.c ./main.c -I ../mandatory/get_next_line.h
	./a.out

bonus :
	gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -D BONUS ../bonus/get_next_line_bonus.c ../bonus/get_next_line_utils_bonus.c ./main.c -I ../bonus/get_next_line_bonus.h
	./a.out
update :
	git add get_next_line.h
	git add get_next_line_utils.c
	git add get_next_line.c
	git commit -m "autocommit"
	git push

clean :
	rm a.out
