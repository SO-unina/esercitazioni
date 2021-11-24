#!/bin/bash

ipcs -m | awk '{print $2}'|grep -vE '(status|ID|Queues|Memory)'|xargs -I {} ipcrm -m {}
echo "Removed IPC shared memories"

ipcs -q | awk '{print $2}'|grep -vE '(status|ID|Queues|Memory)'|xargs -I {} ipcrm -q {}
echo "Removed IPC queues"

ipcs -s | awk '{print $2}'|grep -vE '(status|ID|Queues|Memory)'|xargs -I {} ipcrm -s {}
echo "Removed IPC semaphores"
