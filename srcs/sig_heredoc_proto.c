
void	handle_sig(int sig)
{
	int				fd;
	int				io;
	struct termios	old_term;
	struct termios	new_term;

	fd = open("/dev/tty", O_RDWR);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (tcgetattr(fd, &old_term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	new_term = old_term;
	new_term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(fd, TCSANOW, &new_term) == -1)
	{
		perror("tcsetattr");
		return ;
	}
	if (ioctl(fd, TIOCSTI, "\n") == -1)
	{
		perror("ioctl");
		return ;
	}
	if (tcsetattr(fd, TCSANOW, &old_term) == -1)
	{
		perror("tcsetattr");
		return ;
	}
}
