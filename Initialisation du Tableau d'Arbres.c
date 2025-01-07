#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} Node, *tree;

//* دالة لإنشاء عقدة جديدة
tree createNode(int value) {
    tree newNode = (tree)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL; // فشل تخصيص الذاكرة
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//* دالة لإضافة قيمة إلى شجرة
void add(tree* arber, int value) {
    if (*arber == NULL) {
        *arber = createNode(value); // إنشاء عقدة جديدة في الشجرة إذا كانت فارغة
        return;
    }
    if (value < (*arber)->value) {
        add(&(*arber)->left, value); // إضافة القيمة في الفرع الأيسر
    } else if (value > (*arber)->value) {
        add(&(*arber)->right, value); // إضافة القيمة في الفرع الأيمن
    }
}

//* دالة لإضافة قيمة إلى موقع معين في مصفوفة الأشجار
void Ajout_d_une_Valeur_à_une_Case(tree* arrayTree, int index, int value, int size) {
    if (index < 0 || index >= size) {
        printf("erreur\n");
        return;
    }
    if (arrayTree[index] == NULL) {
        arrayTree[index] = createNode(value); // إذا كانت الشجرة فارغة، قم بإنشاء عقدة جديدة
    } else {
        add(&arrayTree[index], value); // إضافة القيمة في الشجرة الحالية
    }
}

//* دالة لتهيئة مصفوفة الأشجار
tree* Initializing_the_Tree_Table(int n) {
    tree* arrytree = (tree*)malloc(n * sizeof(tree)); // تخصيص الذاكرة لمصفوفة الأشجار
    if (arrytree == NULL) {
        return NULL; // فشل تخصيص الذاكرة
    }
    for (int i = 0; i < n; i++) {
        arrytree[i] = NULL; // تعيين كل عنصر في المصفوفة إلى NULL
    }
    return arrytree;
}

//* دالة لملء الأشجار بعدد عشوائي من العقد
void fill_With_Random_Values(tree* arrytree, int n, int N) {
    for (int i = 0; i < N; i++) {
        int numNodes = rand() % n + 1;  // عدد عشوائي من العقد بين 1 و n
        printf("Filling tree %d with %d nodes.\n", i + 1, numNodes);

        for (int j = 0; j < numNodes; j++) {
            int Value = rand() % 1001;  // قيمة عشوائية بين 0 و 1000
            Ajout_d_une_Valeur_à_une_Case(arrytree, i, Value, n); // إضافة القيمة إلى الشجرة
            printf("Added value %d to tree %d.\n", Value, i + 1);
        }
    }
}

//* دالة لعرض الشجرة بشكل هرمي
void print(tree arrytree, int space) {
    if (arrytree == NULL) return;
    space += 4; // زيادة المسافة للطباعة بشكل هرمي
    print(arrytree->right, space); // طباعة الفرع الأيمن
    printf("\n");
    for (int i = 0; i < space; i++) {
        printf(" "); // مسافة لزيادة التباعد بين العقد
    }
    printf("%d", arrytree->value); // طباعة قيمة العقدة
    print(arrytree->left, space); // طباعة الفرع الأيسر
}

//* دالة لإجراء ترتيب باستخدام خوارزمية الفقاعة (Bubble Sort)
void par_bulles(tree* arrytree, int N, int max) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            // ترتيب تصاعديًا أو تنازليًا بناءً على القيمة في max
            if ((max == 1 && arrytree[j]->value > arrytree[j + 1]->value) ||
                (max == 0 && arrytree[j]->value < arrytree[j + 1]->value)) {
                tree temp = arrytree[j];
                arrytree[j] = arrytree[j + 1];
                arrytree[j + 1] = temp;
            }
        }
    }
}

//* دالة لإجراء ترتيب باستخدام خوارزمية الاختيار (Selection Sort)
void par_sélection(tree* arrytree, int n, int max) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            // ترتيب تصاعديًا أو تنازليًا بناءً على القيمة في max
            if ((max == 1 && arrytree[j]->value > arrytree[minIndex]->value) ||
                (max == 0 && arrytree[j]->value < arrytree[minIndex]->value)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tree temp = arrytree[i];
            arrytree[i] = arrytree[minIndex];
            arrytree[minIndex] = temp;
        }
    }
}

//* دالة لتحرير الذاكرة المُخصصة للأشجار
void freee(tree* arrytree, int n) {
    for (int i = 0; i < n; i++) {
        if (arrytree[i] != NULL) {
            if (arrytree[i]->left != NULL) {
                freee(&arrytree[i]->left, 1); // تحرير الذاكرة للفرع الأيسر
            }
            if (arrytree[i]->right != NULL) {
                freee(&arrytree[i]->right, 1); // تحرير الذاكرة للفرع الأيمن
            }
            free(arrytree[i]); // تحرير الذاكرة للعقدة الحالية
        }
    }
    free(arrytree); // تحرير الذاكرة للمصفوفة
}

//* دالة للطباعة بترتيب ما قبل الترتيب (Pre-order)
void Préfixe(tree arbre) {
    if (arbre == NULL) return;
    printf("%d ", arbre->value); // طباعة قيمة العقدة
    Préfixe(arbre->left); // استدعاء دالة ما قبل الترتيب للفرع الأيسر
    Préfixe(arbre->right); // استدعاء دالة ما قبل الترتيب للفرع الأيمن
}

//* دالة للطباعة بترتيب الترتيب الوسيط (In-order)
void Infixe(tree arbre) {
    if (arbre == NULL) return;
    Infixe(arbre->left); // استدعاء دالة الترتيب الوسيط للفرع الأيسر
    printf("%d ", arbre->value); // طباعة قيمة العقدة
    Infixe(arbre->right); // استدعاء دالة الترتيب الوسيط للفرع الأيمن
}

//* دالة للطباعة بترتيب ما بعد الترتيب (Post-order)
void Postfixe(tree arbre) {
    if (arbre == NULL) return;
    Postfixe(arbre->left); // استدعاء دالة ما بعد الترتيب للفرع الأيسر
    Postfixe(arbre->right); // استدعاء دالة ما بعد الترتيب للفرع الأيمن
    printf("%d ", arbre->value); // طباعة قيمة العقدة
}

int main() {
    int n; // عدد الأشجار
    printf("Enter the number of trees: ");
    scanf("%d", &n);

    //* تهيئة مصفوفة الأشجار
    tree* arrytree = Initializing_the_Tree_Table(n);
    if (arrytree == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // فشل تخصيص الذاكرة
    }

    int choice;
    while (choice != 15) {
        menu(); // عرض القائمة
        printf("Enter your choice {its number }: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int treeIndex, value;
                printf("Enter the tree index (0 to %d) and value: ", n - 1);
                scanf("%d %d", &treeIndex, &value);
                Ajout_d_une_Valeur_à_une_Case(arrytree, treeIndex, value, n);
                break;
            }
            // بقية الخيارات...

            case 15:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    //* تحرير الذاكرة
    freee(arrytree, n);

    return 0;
}
