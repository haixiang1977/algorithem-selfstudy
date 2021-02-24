// generate the gernal tree example
// read directory stucture and print as a tree
// g++ -g -O0 general_tree_create.cpp -o general_tree_create.out

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// check file or directory
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// check directory elements
#include <dirent.h>

// c++ data structure
#include <string>
#include <vector>

using namespace std;

// tree node definiation
class TreeNode
{
 public:
    std::string            m_name;
    TreeNode*              m_parent;
    std::vector<TreeNode*> m_children_list;
};

TreeNode* root = NULL;

char* concat(char* s1, char* s2)
{
    char* s = (char*)malloc(strlen(s1) + strlen("/") + strlen(s2) + 1);
    strcpy(s, s1);
    strcat(s, "/");
    strcat(s, s2);
    return s;
}

int is_directory(char* path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
    {
        return -1;
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        return 1;
    }

    return 0;
}

void parse_dir(char* path, TreeNode* node)
{
    struct dirent **namelist;

    // printf("scandir %s\n", path);
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
        exit (1);
    }

    while (n--)
    {
        // print the file or directory without "." and "../"
        if (strcmp(namelist[n]->d_name, ".") && strcmp(namelist[n]->d_name, ".."))
        {
            TreeNode* child = new TreeNode();

	        child->m_parent = node;
	        child->m_name = std::string(namelist[n]->d_name);
	        node->m_children_list.push_back(child);

            // check file or directory
            char* full_path = concat(path, namelist[n]->d_name);
            // printf("full path name: %s\n", full_path);
            int is_dir = is_directory(full_path);
            // printf("name:%s %s\n", namelist[n]->d_name, ((is_dir == 1) ? "directory" : "file"));
            if (is_dir)
            {
                // parse sub directory
                parse_dir(full_path, child);
	        }
        }
        free(namelist[n]);
    }
    free(namelist);

    return;
}

void dump_tree(TreeNode* node, int indent)
{
    if (node == NULL)
        return;

    for (int i = 0; i < (int)node->m_children_list.size(); i++)
    {
	    for (int j = 0; j < indent; j++)
	    {
	        printf(" ");
	    }
        printf("%s\n", node->m_children_list[i]->m_name.c_str());
	    dump_tree(node->m_children_list[i], indent + 4);
    }

    return;
}

int main(int argc, char *argv[])
{
    char* path;

    // read input parameter
    if (argc < 2)
    {
        path = strdup("./");
    }
    else
    {
        path = strdup(argv[1]);
    }
    printf("list path %s:\n", path);

    // parse the directory
    root = new TreeNode();
    root->m_parent = NULL;
    root->m_name = std::string(path);
    parse_dir(path, root);

    // print the directory
    dump_tree(root, 0);

    free(path);

    return 0;
}
