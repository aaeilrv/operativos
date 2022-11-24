/**
 * Valeria Vera
 * 16-11233
 * Sistemas de Operación I
 * 
 * Funciones auxiliares para el proyecto I.
*/

#ifndef __AUXFUNCTIONS_H__
#define __AUXFUNCTIONS_H__

#include <stdio.h>

Node* searchInode(int inode, Lista* inode_list);
int is_directory(char* path);
int is_reg_file(char* path);
int is_symbolic_link(char* path);
int calc_size(char* path);
int inode_number(char* path);
int duplicated_inode(Lista* inodes_list, char* path);
int recursiveVisit(char* dirname, char* indent, Array* array, Lista* inodes_list);
void sort(Array* array);
void hierarchyTree(Array* values, FILE* fp, Lista* inodes_list);
char* beggining(int argc, char** argv);
FILE* output(int argc, char** argv);

#endif