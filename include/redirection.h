#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>

/* std_backup */
void		std_save(int *stdin, int *stdout, int *stderr);
void		std_restore(int stdin, int stdout, int stderr);

/* heredoc */
int			heredoc_tmp_file_delete(int tmp_count);
#endif
