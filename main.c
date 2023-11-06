#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    char *key_and_color;
    struct node *p;
    struct node *left;
    struct node *right;
    struct node *next;
} node;

typedef struct BST_node{
    node * pointer;
    struct BST_node *left, *right;
} BST_node;

typedef struct symbols {
    char s[64];
} symbols;

typedef struct constraints{
    symbols * accepted;
    char * assured;
    int occ_q[64];
} constraints;

node *NIL, *list_NIL;
node ** dictionary;
node *list, *fix_list_pointer, *prev_fix_list_pointer;
node * new_node;
BST_node *temp_tree, *bst_NIL;
char st;
int k, length;
constraints cnst;
char *w;
const char alphabet[64] = "uABCDEFGHIJKLMNOPQRSTUVWXYZvwxy_zabcdefghijkl-mn0123456789opqrst";
const int HASH_size = 64;
char *goal;
int n;
char first_filter;

BST_node * BST_insert(BST_node *t, node *pointer) {
    BST_node *y;
    y = bst_NIL;
    BST_node *x = t;
    while(x != bst_NIL) {
        y = x;
        if(strncmp(pointer->key_and_color, x->pointer->key_and_color, k) < 0){
            x = (*x).left;
        }
        else {
            x = (*x).right;
        }
    }
    BST_node *z;
    z = (BST_node *) malloc(sizeof(BST_node));
    (*z).left = bst_NIL;
    (*z).right = bst_NIL;
    z->pointer = pointer;
    if(y == bst_NIL)
        return z;
    else {
        if (strncmp(z->pointer->key_and_color, y->pointer->key_and_color, n) < 0)
            (*y).left = z;
        else
            (*y).right = z;
    }
    return t;
}

char RB_exists(node *t, char *word) {
    if(t == NIL)
        return 'f';
    if(strncmp(word, t->key_and_color, k)==0)
        return 't';
    if(strncmp(word, t->key_and_color, k)<0)
        return RB_exists(t->left, word);
    return RB_exists(t->right, word);
}

node * left_rotate(node * t,node * x) {
    node * y = x->right;
    x->right = y->left;
    if(x->right != NIL)
        x->right->p = x;
    y->p = x->p;
    if(x->p == NIL)
        t = y;
    else
    if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
    return t;
}

node * right_rotate(node * t,node * x) {
    node * y = x->left;
    x->left = y->right;
    if(y->right != NIL)
        y->right->p = x;
    y->p = x->p;
    if(y->p == NIL)
        t = y;
    else
    if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
    return t;
}

node * RB_insert_fixup(node * t, node * z) {
    node *x, *y;
    if(z == t)
        t->key_and_color[k] = '?';
    else {
        x = z->p;
        if(x->key_and_color[k] == '!') {
            if (x == x->p->left) {
                y = x->p->right;
                if (y->key_and_color[k] == '!') {
                    x->key_and_color[k] = '?';
                    y->key_and_color[k] = '?';
                    x->p->key_and_color[k] = '!';
                    return RB_insert_fixup(t, x->p);
                } else {
                    if (z == x->right) {
                        z = x;
                        t = left_rotate(t, z);
                        x = z->p;
                    }
                    x->key_and_color[k] = '?';
                    x->p->key_and_color[k] = '!';
                    t = right_rotate(t, x->p);
                }
            } else {
                y = x->p->left;
                if (y->key_and_color[k] == '!') {
                    x->key_and_color[k] = '?';
                    y->key_and_color[k] = '?';
                    x->p->key_and_color[k] = '!';
                    return RB_insert_fixup(t, x->p);
                } else {
                    if (z == x->left) {
                        z = x;
                        t = right_rotate(t, z);
                        x = z->p;
                    }
                    x->key_and_color[k] = '?';
                    x->p->key_and_color[k] = '!';
                    t = left_rotate(t, x->p);
                }
            }
        }
    }
    return t;
}

void list_delete(node * prev, node * x) {
    if(prev != list_NIL)
        prev->next = x->next;
    else
        list = x->next;
    x->next = NIL;
    length--;
}

void list_insert(node *x) {
    if(list == list_NIL) {
        list = x;
        x->next = list_NIL;
    }
    else {
        x->next = list;
        list = x;
    }
    length++;
}

void list_fix(BST_node *x) {
    if(x != bst_NIL) {
        list_fix(x->left);
        while(fix_list_pointer != list_NIL && strncmp(x->pointer->key_and_color, fix_list_pointer->key_and_color,  k) > 0) {
            prev_fix_list_pointer = fix_list_pointer;
            fix_list_pointer = fix_list_pointer->next;
        }
        if(prev_fix_list_pointer == list_NIL) {
            x->pointer->next = list;
            list = x->pointer;
        }
        else {
            prev_fix_list_pointer->next = x->pointer;
            x->pointer->next = fix_list_pointer;
        }
        prev_fix_list_pointer = x->pointer;
        length++;
        list_fix(x->right);
        free(x);
    }
}

node * RB_insert(node *t, char *word) {
    node *y;
    y = NIL;
    node *x = t;
    while (x != NIL) {
        y = x;
        if (strncmp(word, (*x).key_and_color, k) < 0) {
            x = (*x).left;
        } else {
            x = (*x).right;
        }
    }
    node *z;

    z = (node *) malloc(sizeof(node));
    (*z).key_and_color = (char *) malloc((k + 2) * sizeof(char));
    for(short i=0; i<k; i++)
        z->key_and_color[i] = word[i];
    (*z).p = y;
    if (y == NIL)
        t = z;
    else {
        if (strncmp((*z).key_and_color, (*y).key_and_color, k) < 0)
            (*y).left = z;
        else
            (*y).right = z;
    }
    (*z).left = NIL;
    (*z).right = NIL;
    z->key_and_color[k] = '!';
    z->key_and_color[k+1] = '\0';
    z->next = NIL;
    t = RB_insert_fixup(t, z);
    new_node = z;
    return t;
}

void RB_inorder_tree_walk(node *t) {
    if(t != NIL) {
        RB_inorder_tree_walk(t->left);
        int * i = (int * )malloc(sizeof (int));
        for(i[0]=0; i[0]<k; i[0]++)
            printf("%c", t->key_and_color[i[0]]);
        printf("\n");
        free(i);
        RB_inorder_tree_walk(t->right);
    }
}

int get_char_pos(char c) {
    int i = 0;
    while((int) c != alphabet[((int)c+i)%64])
        i++;
    return ((int)c+i)%64;
}

char must_delete(const char * word) {
    for(short i=0; i<k; i++) {
        if(cnst.assured[i] != '*') {
            if (cnst.assured[i] != word[i])
                return 't';
            else
                continue;
        }
        if (cnst.accepted[i].s[get_char_pos(word[i])] == '*')
            return 't';
    }

    short temp_occ[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(short i=0; i<k; i++)
        temp_occ[get_char_pos(word[i])]++;

    int c = 0;
    for(short i=0; i<64; i++) {
        if(cnst.occ_q[i] != 0) {
            if (cnst.occ_q[i] < 0) {
                if (temp_occ[i] != (-1 * cnst.occ_q[i]))
                    return 't';
                c+=(-1*cnst.occ_q[i]);
            } else {
                if (temp_occ[i] < cnst.occ_q[i])
                    return 't';
                c+=cnst.occ_q[i];
            }
            if(c>=k)
                break;
        }
    }
    return 'f';
}

void first_filter_1(node *t, char c, short pos) {
    if(t!=NIL) {
        first_filter_1(t->right, c, pos);
        if (t->key_and_color[pos] == c)
            list_insert(t);
        first_filter_1(t->left, c, pos);
    }
}

void filter_1(char c, short pos) {
    if(first_filter == 'f') {
        node *x = list, *y = list_NIL, *z;
        while (x != list_NIL) {
            z = x->next;
            if (x->key_and_color[pos] != c) {
                list_delete(y, x);
            } else
                y = x;
            x = z;
        }
    }
    else {
        int *i = (int *) malloc(sizeof (int));
        for(i[0]=HASH_size-1; i[0]>=0; i[0]--)
            first_filter_1(dictionary[i[0]], c, pos);
        first_filter = 'f';
        free(i);
    }
}

void first_filter_2(node *t, char c, short pos) {
    if(t!=NIL) {
        first_filter_2(t->right, c, pos);
        if (t->key_and_color[pos] != c && strchr(t->key_and_color, c) != NULL)
            list_insert(t);
        first_filter_2(t->left, c, pos);
    }
}

void filter_2(char c, short pos) {
    if(first_filter == 'f') {
        node *x = list, *y = list_NIL, *z;
        while (x != list_NIL) {
            z = x->next;
            if (x->key_and_color[pos] == c)
                list_delete(y, x);
            else if (strchr(x->key_and_color, c) == NULL)
                list_delete(y, x);
            else
                y = x;
            x = z;
        }
    }
    else {
        int *i = (int *) malloc(sizeof (int));
        for(i[0]=HASH_size-1; i[0]>=0; i[0]--)
            first_filter_2(dictionary[i[0]], c, pos);
        first_filter = 'f';
        free(i);
    }
}

void first_filter_3(node *t, char c) {
    if(t!=NIL) {
        first_filter_3(t->right, c);
        if (strchr(t->key_and_color, c) == NULL)
            list_insert(t);
        first_filter_3(t->left, c);
    }
}

void filter_3(char c){
    if(first_filter == 'f') {
        node *x = list, *y = list_NIL, *z;
        while (x != list_NIL) {
            z = x->next;
            if (strchr(x->key_and_color, c) != NULL)
                list_delete(y, x);
            else
                y = x;
            x = z;
        }
    }
    else {
        int *i = (int *) malloc(sizeof (int));
        for(i[0]=HASH_size-1; i[0]>=0; i[0]--)
            first_filter_3(dictionary[i[0]], c);
        first_filter = 'f';
        free(i);
    }
}

void first_filter_4(node *t, char c, short pos, short q) {
    if(t!=NIL) {
        first_filter_4(t->right, c, pos, q);
        if (t->key_and_color[pos] != c) {
            short * count = (short *) malloc(sizeof (short));
            count[0] = 0;
            short * i = (short *) malloc(sizeof (short));
            for (i[0] = 0; i[0] < k; i[0]++)
                if(t->key_and_color[i[0]] == c)
                    count[0]++;
            if(count[0] == q)
                list_insert(t);
            free(count);
            free(i);
        }
        first_filter_4(t->left, c, pos, q);
    }
}

void filter_4(char c, short pos, short q){
    if(first_filter == 'f') {
        node * x = list, *y = list_NIL, *z;
        while(x != list_NIL) {
            z = x->next;
            if (x->key_and_color[pos] == c)
                list_delete(y, x);
            else {
                short * count = (short *) malloc(sizeof (short));
                count[0] = 0;
                short * i = (short *) malloc(sizeof (short));
                for (i[0] = 0; i[0] < k; i[0]++)
                    if(x->key_and_color[i[0]] == c)
                        count[0]++;
                if(count[0] != q)
                    list_delete(y, x);
                else
                    y = x;
                free(count);
                free(i);
            }
            x = z;
        }
    }
    else {
        int *i = (int *) malloc(sizeof (int));
        for(i[0]=HASH_size-1; i[0]>=0; i[0]--)
            first_filter_4(dictionary[i[0]], c, pos, q);
        first_filter = 'f';
        free(i);
    }
}

void first_filter_5(node *t, char c, short q) {
    if(t!=NIL) {
        first_filter_5(t->right, c, q);
        short *count = (short *) malloc(sizeof(short));
        count[0] = 0;
        short *i = (short *) malloc(sizeof(short));
        for (i[0] = 0; i[0] < k; i[0]++)
            if (t->key_and_color[i[0]] == c)
                count[0]++;
        if (count[0] >= q)
            list_insert(t);
        free(count);
        free(i);
        first_filter_5(t->left, c, q);
    }
}

void filter_5(char c, short q){
    if(first_filter == 'f') {
        node *x = list, *y = list_NIL, *z;
        while (x != list_NIL) {
            z = x->next;
            short *count = (short *) malloc(sizeof(short));
            count[0] = 0;
            short *i = (short *) malloc(sizeof(short));
            for (i[0] = 0; i[0] < k; i[0]++)
                if (x->key_and_color[i[0]] == c)
                    count[0]++;
            if (count[0] < q)
                list_delete(y, x);
            else
                y = x;
            x = z;
            free(count);
            free(i);
        }
    }
    else {
        int *i = (int *) malloc(sizeof (int));
        for(i[0]=HASH_size-1; i[0]>=0; i[0]--)
            first_filter_5(dictionary[i[0]], c, q);
        first_filter = 'f';
        free(i);
    }
}

void check_word(const char * word) {
    char output[k];
    char checker[k];
    short temp_occ[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(short i=0; i<k; i++) {
        output[i] = '/';
        checker[i] = 't';
    }

    for(short i=0; i<k; i++)
        if(word[i] == goal[i]) {
            output[i] = '+';
            checker[i] = 'f';
            if(cnst.assured[i] == '*'){
                filter_1(word[i], i);
                cnst.assured[i] = word[i];
            }
            temp_occ[get_char_pos(word[i])]++;
        }

    for(short i=0; i<k; i++){
        if(output[i] == '+')
            continue;
        int p = get_char_pos(word[i]);
        char found[2] = {'f', 'f'};
        for(short j=0; j<k; j++){
            if(word[i] == goal[j]){
                if(checker[j] == 't') {
                    checker[j] = 'f';
                    output[i] = '|';
                    if(cnst.accepted[i].s[p] != '*') {
                        filter_2(word[i], i);
                        cnst.accepted[i].s[p] = '*';
                    }
                    temp_occ[p]++;
                    found[1] = 't';
                    break;
                }
                found[0] = 't';
            }
        }

        if(found[0] == 'f' && found[1] == 'f') {
            char must_filter = 'f';
            for (short j = 0; j < k; j++)
                if(cnst.accepted[j].s[p] != '*') {
                    must_filter = 't';
                    cnst.accepted[j].s[p] = '*';
                }
            if(must_filter == 't')
                filter_3(word[i]);
        }

        if(found[0] == 't' && found[1] == 'f'){
            char must_filter = 'f';
            if(cnst.accepted[i].s[p] != '*') {
                must_filter = 't';
                cnst.accepted[i].s[p] = '*';
            }
            if(cnst.occ_q[p] != -1 * temp_occ[p]) {
                must_filter = 't';
                cnst.occ_q[p] = -1 * temp_occ[p];
            }
            if(must_filter == 't')
                filter_4(word[i], i, temp_occ[p]);
        }
    }

    for(short i=0; i<64; i++)
        if(cnst.occ_q[i]>=0 && cnst.occ_q[i]<temp_occ[i])
            if(cnst.occ_q[i] != temp_occ[i]) {
                cnst.occ_q[i] = temp_occ[i];
                filter_5(alphabet[i], cnst.occ_q[i]);
            }

    for(short i=0; i<k; i++)
        printf("%c", output[i]);
    printf("\n");
}

void restore() {
    node * x = list;
    while (x != list_NIL) {
        list = x->next;
        x->next = NIL;
        x = list;
        length--;
    }
}

int HASH_function(const char *word) {
    int c = (int) word[0];

    if(c>=65 && c<=90)
        return c-54;

    if(c>=97 && c<=122)
        return c-59;

    if(c >= 48 && c <=57)
        return c-47;

    if(c == 45)
        return 0;

    if(c == 95)
        return 37;

    return -1;
}

void print_filtered() {
    if(first_filter == 'f') {
        node *x = list;
        while (x != list_NIL) {
            char *word = (char *) malloc((k + 1) * sizeof(char));
            for (short i = 0; i < k; i++)
                word[i] = x->key_and_color[i];
            word[k] = '\0';
            printf("%s\n", word);
            x = x->next;
        }
    }
    else
        for(int i=0; i<HASH_size; i++)
            RB_inorder_tree_walk(dictionary[i]);
}

char exists(char *word) {
    node * tree = dictionary[HASH_function(word)];
    return RB_exists(tree, word);
}

void HASH_insert(char *word) {
    int p = HASH_function(word);
    dictionary[p] = RB_insert(dictionary[p], word);
}

int start() {
    st = 'a';
    if (scanf("%d", &k) <= 0) return 0;
    NIL = (node *) malloc(sizeof(node));
    NIL->key_and_color = malloc((k+2)*sizeof (char));
    for(short i=0; i<k; i++)
        NIL->key_and_color[i] = '*';
    list_NIL = (node *) malloc(sizeof(node));
    NIL->key_and_color[k] = '?';
    NIL->key_and_color[k+1] = '\0';
    dictionary = (node **) malloc(HASH_size * sizeof(node *));
    for (int i = 0; i < HASH_size; i++)
        dictionary[i] = NIL;
    list = list_NIL;
    fix_list_pointer = list_NIL;
    bst_NIL = (BST_node *) malloc(sizeof (BST_node));
    temp_tree = bst_NIL;
    length = 0;
    first_filter = 't';
    cnst.accepted = (symbols *) malloc((k + 1) * sizeof(symbols));
    cnst.assured = (char *) malloc((k + 1) * sizeof(char));
    goal = (char *) malloc((k + 1) * sizeof(char));
    if (k >= 18)
        w = (char *) malloc((k + 1) * sizeof(char));
    else
        w = (char *) malloc(18 * sizeof(char));
    return 0;
}

int first_insert() {
    if(getchar_unlocked()<=0) return 0;
    while ('t') {
        short * i = (short *) malloc(sizeof (short));
        for(i[0]=0; (w[i[0]]=getchar_unlocked())!='\n';i[0]++)
            if(w[i[0]] <= 0)
                return 0;
        w[i[0]] = '\0';
        free(i);
        if (w[0] == '+') {

            if (strcmp(w, "+nuova_partita") == 0) {
                break;
            }

            if (strcmp(w, "+stampa_filtrate") == 0) {
                print_filtered();
                continue;
            }

        } else {
            HASH_insert(w);
        }
    }
    return 0;
}

int play(){
    first_filter = 't';
    char found = 'f';
    st = 'p';
    char prev_st = 'p';
    short * i = (short *) malloc(sizeof (short));
    for(i[0]=0; i[0]<k; i[0]++) {
        strcpy(cnst.accepted[i[0]].s, "uABCDEFGHIJKLMNOPQRSTUVWXYZvwxy_zabcdefghijkl-mn0123456789opqrst");
        cnst.assured[i[0]] = '*';
    }
    for(i[0]=0; i[0]<64; i[0]++)
        cnst.occ_q[i[0]] = 0;

    if (scanf("%s", goal) <= 0) return 1;
    if (scanf("%d", &n) <= 0) return 1;
    i[0] = 0;
    if(getchar_unlocked() <=0) return 0;
    while ('t') {

        if (i[0] == n && st == 'p') {
            printf("ko\n");
            st = 'e';
            continue;
        }

        short * j = (short *) malloc(sizeof (short));
        for(j[0]=0; (w[j[0]]=getchar_unlocked())!='\n';j[0]++)
            if(w[j[0]] <= 0)
                return 0;
        w[j[0]] = '\0';
        free(j);

        if(w[0] != '+') {
            if(st == 'p') {
                if (exists(w) == 't') {
                    if (strcmp(w, goal) == 0) {
                        printf("ok\n");
                        found = 't';
                        st = 'e';
                        continue;
                    }
                    check_word(w);
                    printf("%d\n", length);
                    i[0]++;
                } else
                    printf("not_exists\n");
                continue;
            }

            if(st=='j') {
                HASH_insert(w);
                if(prev_st == 'p' && first_filter == 'f')
                    if(must_delete(w) == 'f')
                        temp_tree = BST_insert(temp_tree, new_node);
                continue;
            }
        }
        else{
            if (strcmp(w, "+stampa_filtrate") == 0) {
                if(found == 'f')
                    print_filtered();
                else
                    printf("%s\n", goal);
                continue;
            }

            if (strcmp(w, "+inserisci_inizio") == 0) {
                if (st == 'p' || st == 'e') {
                    prev_st = st;
                    st = 'j';
                }
                continue;
            }

            if (strcmp(w, "+inserisci_fine") == 0) {
                if(prev_st == 'p') {
                    fix_list_pointer = list;
                    prev_fix_list_pointer = list_NIL;
                    list_fix(temp_tree);
                    temp_tree = bst_NIL;
                }
                if (st == 'j')
                    st = prev_st;
                continue;
            }

            if (strcmp(w, "+nuova_partita") == 0) {
                restore();
                st = 'p';
                break;
            }
        }
    }
    free(i);
    return 0;
}

int main() {
    start();
    first_insert();
    while (play() == 0);

    return 0;
}