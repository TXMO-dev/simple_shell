# simple_shell
this the simple shell test for the alx programme

     +------------+
       | Start loop |
       +-----+------+
             |
             v
    +--------------------+
    | Display prompt ">$" |
    +-----------+--------+
                |
                v
       +----------------------+
       | Read command from user |
       +-----------+----------+
                   |
                   v
       +-------------------------+
       | Parse command into args |
       +-----------+-------------+
                   |
                   v
        +-----------------------+
        | Check for exit command |
        +-----------+-----------+
                    |
                    v
        +---------------------------+
        | Create child process with fork() |
        +-----------+---------------+
                    |
                    v
        +----------------------------+
        | Execute command in child process |
        +-----------+----------------+
                    |
                    v
        +--------------------------+
        | Wait for child to complete |
        +-----------+--------------+
                    |
                    v
        +-----------------------------+
        | Return to top of loop and repeat |
        +-----------------------------+
