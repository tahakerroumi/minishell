

int pipefd[2];

while (cmd->next)
{
        ret_val = pipe(pipefd);
        // protect pipe

        cmd->pipefd[1] = pipefd[1];
        cmd->next->pipefd[0] = pipefd[0];

        cmd->pid = fork();
        // protect fork

        if (!cmd->pid)
                child_routine(cmd); // it must have exit() at the end of the routine

        if (cmd->pipefd[0])
                close(cmd->pipefd[0]);
        if (cmd->pipefd[1])
                close(cmd->pipefd[1]);

        
        cmd = next>next;
}

if (cmd->pipefd[0] || !is_builtin(cmd))
{       
        cmd->pid = fork();
        // protect fork

        if (!cmd->pid)
                child_routine(cmd); // it must have exit() at the end of the routine

        if (cmd->pipefd[0])
                close(cmd->pipefd[0]);

        // wait for all the child processes then get the exit status of the last process
        // funtion for waiting
}
else
        run_builtin(cmd);    




