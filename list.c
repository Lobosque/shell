#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void ListCreate(LIST *list)
{
    list->first = NULL;
    list->last = NULL;
}

void initCommand(COMMAND *cmd)
{
    cmd->isBackground = 0;
    cmd->input_r = 0;
    cmd->output_r = 0;
    cmd->output_r_append = 0;
    cmd->size = 0;
    cmd->id = -1;
    cmd->pid = -1;
    cmd->pipe[0] = -1;
    cmd->pipe[1] = -1;
}

int ListIsEmpty(LIST *list)
{
    if(list->first == NULL) return 1;
    return 0;
}


int ListInsert(LIST *list, PROCESS *proc, COMMAND *cmd)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    if (newNode != NULL)
    {
        newNode->proc = proc;
        newNode->cmd = cmd;
        newNode->next = NULL;
        newNode->prev = list->last;

        if (list->last != NULL)
            list->last->next = newNode;
        else
            list->first = newNode;

        list->last = newNode;
        return 1;
    }
    return 0;
}

int ListGetByPid(LIST *list, pid_t pid, PROCESS *proc)
{
    NODE *aux = list->first;
    while (aux != NULL)
    {
        if (aux->proc->pid == pid)
        {
            proc = aux->proc;
            return 1;
        }
        aux = aux->next;
    }

    return 0;
}

int ListStopRunningProcessByPid(LIST *list, pid_t pid)
{
    NODE *aux = list->first;
    while (aux != NULL)
    {
        if((strcmp(aux->proc->status, "Running") == 0) && aux->proc->pid == pid)
        {
            strcpy(aux->proc->status, "Stopped");
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}


int ListRemoveByPid(LIST *list, pid_t pid)
{
    if (!ListIsEmpty(list))
    {
        NODE *aux = list->first;

        while(aux->proc->pid != pid)
        {
            if (aux != list->last)
                aux = aux->next;
            else return 0;
        }

        if (aux == list->first)
            list->first = aux->next;
        else
            aux->prev->next = aux->next;

        if (aux == list->last)
            list->last = aux->prev;
        else
            aux->next->prev = aux->prev;

        free(aux->proc);
        free(aux);

        return 1;
    }
    return 0;
}

pid_t ListLastStoppedToBg(LIST *list)
{
    if(!ListIsEmpty(list))
    {
        NODE *aux = list->last;
        while (aux != NULL)
        {
            if(strcmp(aux->proc->status, "Stopped") == 0)
            {
                aux->proc->isBackground = 1;
                strcpy(aux->proc->status, "Running");
                return aux->proc->pid;
            }
            aux = aux->prev;
        }
    }
    return -1;
}

pid_t ListToBg(LIST *list, pid_t pid)
{
    if(!ListIsEmpty(list))
    {
        NODE *aux = list->last;
        while (aux != NULL)
        {
            if(aux->proc->pid == pid)
            {
                aux->proc->isBackground = 1;
                strcpy(aux->proc->status, "Running");
                return aux->proc->pid;
            }
            aux = aux->prev;
        }
    }
    return -1;
}

pid_t ListLastToFg(LIST *list)
{
    if(!ListIsEmpty(list))
    {
        NODE *aux = list->last;
        if (aux != NULL)
        {
            aux->proc->isBackground = 0;
            strcpy(aux->proc->status, "Running");
            return aux->proc->pid;
        }
        aux = aux->prev;
    }
    return -1;
}

pid_t ListToFg(LIST *list, pid_t pid)
{
    if(!ListIsEmpty(list))
    {
        NODE *aux = list->last;
        while (aux != NULL)
        {
            if(aux->proc->pid == pid)
            {
                aux->proc->isBackground = 0;
                strcpy(aux->proc->status, "Running");
                return aux->proc->pid;
            }
            aux = aux->prev;
        }
    }
    return -1;
}

void ListPurgeCmds(LIST *list)
{
    if(!ListIsEmpty(list))
    {
        NODE *aux = list->first;
        while(aux != NULL)
        {
            int i;
            for(i = 0; i < aux->cmd->size; i++)
                free(aux->cmd->args[i]);
            free(aux->cmd->args);
            free(aux->cmd);
            aux = aux->next;
        }
        ListCreate(list);
    }
}

