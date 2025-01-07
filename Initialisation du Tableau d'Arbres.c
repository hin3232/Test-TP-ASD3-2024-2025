#include <stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct node {
    int value;
    struct node*left;
    struct node*right;
}Node,*tree;

tree createNode(int value) {
    tree newNode = (tree)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//* دالة لإضافة قيمة إلى شجرة */ 
void add(tree* arber, int value) {
    if (*arber == NULL) {
        *arber = createNode(value); 
        return;
    }
    if (value < (*arber)->value) {
        add(&(*arber)->left, value); 
    } else if (value > (*arber)->value) {
        add(&(*arber)->right, value); 
    }
}
/**دالة لإضافة قيمة إلى موقع معين في مصفوفة الأشجار**/ 
void Ajout_d_une_Valeur_à_une_Case(tree* arrayTree, int index, int value, int size) {
    if (index < 0 || index >= size) {
        printf("erreur\n");
        return;
    }
    if (arrayTree[index] == NULL) {
        arrayTree[index] = createNode(value); 
    } else {
        add(&arrayTree[index], value); }}
tree* Initializing_the_Tree_Table(int n){


    tree* arrytree=(tree*)malloc(n*sizeof(tree));
    if (arrytree==NULL){
       return NULL;
    }
    for (int i=0;i<n;i++){
        arrytree[i]=NULL;
    }return arrytree;
}
//** دالة لملء الأشجار بعدد عشوائي من العقد**//
// دالة لدمج جزئين مفصولين من المصفوفة
void merge(tree* array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // إنشاء مصفوفات مؤقتة للجزئين
    tree* leftArray = (tree*)malloc(n1 * sizeof(tree));
    tree* rightArray = (tree*)malloc(n2 * sizeof(tree));

    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    // دمج الجزئين
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i]->value <= rightArray[j]->value) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // إذا تبقى عناصر في leftArray
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    // إذا تبقى عناصر في rightArray
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }

    // تحرير الذاكرة
    free(leftArray);
    free(rightArray);
}

// دالة فرز بالدمج (Merge Sort)
void mergeSort(tree* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // تحديد المنتصف

        // فرز الجزء الأيسر
        mergeSort(array, left, mid);

        // فرز الجزء الأيمن
        mergeSort(array, mid + 1, right);

        // دمج الجزئين
        merge(array, left, mid, right);
    }
}

void fill_With_Random_Values(tree* arrytree, int n, int N) {
    for (int i = 0; i < N; i++) {
        int numNodes = rand() % n + 1;  //* Nombre aléatoire de nœuds entre 1 et maxNodes*/
        printf("Filling tree %d with %d nodes.\n", i + 1, numNodes);

        for (int j = 0; j < numNodes; j++) {
            int Value = rand() % 1001;  //*Générer une valeur aléatoire entre 0 et 1000*//
            Ajout_d_une_Valeur_à_une_Case(arrytree, i, Value, n);
            printf("Added value %d to tree %d.\n", Value, i + 1);
        }
    }
}
void print(tree arrytree, int space) {
    if (arrytree == NULL) return;
    space += 4;
    print(arrytree->right, space);
    printf("\n");
    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%d", arrytree->value);
    print(arrytree->left, space);
}
//**ترتيب  */
void par_bulles(tree* arrytree, int N, int max) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            //**تصاعديًا */
            if (max == 1) {
                if ( arrytree[j]->value > arrytree[j + 1]->value) {
                  
                    tree temp = arrytree[j];
                    arrytree[j] = arrytree[j + 1];
                    arrytree[j + 1] = temp;
                }
            } else {
                //**تنازليًا */
                if ( arrytree[j]->value < arrytree[j + 1]->value) {
                    
                    tree temp = arrytree[j];
                    arrytree[j] = arrytree[j + 1];
                    arrytree[j + 1] = temp;
                }
            }
        }
    }
}
void par_sélection(tree* arrytree, int n ,int max) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        if (max==1){
        for (int j = i + 1; j < n; j++) {
            if ( arrytree[j]->value > arrytree[minIndex]->value) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tree temp = arrytree[i];
            arrytree[i] = arrytree[minIndex];
            arrytree[minIndex] = temp;
        }}
         else {
        for (int j = i + 1; j < n; j++) {
            if ( arrytree[j]->value < arrytree[minIndex]->value) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tree temp = arrytree[i];
            arrytree[i] = arrytree[minIndex];
            arrytree[minIndex] = temp;
        }}
    }
}

void freee(tree*arrytree,int n){
    for (int i=0;i<n;i++){
        if (arrytree[i]!=NULL){
            if(arrytree[i]->left!=NULL){freee(& arrytree[i]->left,n);}
            if(arrytree[i]->right!=NULL){freee(& arrytree[i]->right,n);}
            free(arrytree[i]);
        }
    } free(arrytree);
}
void Préfixe(tree arbre) {
    if (arbre == NULL) return;
    printf("%d ", arbre->value);      
    Préfixe(arbre->left);             
    Préfixe(arbre->right);            
}
void Infixe(tree arbre) {
    if (arbre == NULL) return;
    Infixe(arbre->left);              
    printf("%d ", arbre->value);      
    Infixe(arbre->right);             
}
void Postfixe(tree arbre) {
    if (arbre == NULL) return;
    Postfixe(arbre->left);            
    Postfixe(arbre->right);           
    printf("%d ", arbre->value);      
}
int Recherche_dans_un_Arbr_d_un_Case(tree arber, int value) {
    int found=0; tree i =arber;
    while ((i!=NULL&&(!found))){
  if (i->value==value){found=1;
  }else if (i->value>value){
    i=i->left;
  }else{
    i=i->right;
    }
}return found;
}
int Recherche_Globale (tree* arrytree, int N, int value) {
    for (int i = 0; i < N; i++) {
        if (Recherche_dans_un_Arbr_d_un_Case(arrytree[i], value)) {  /**إذا وجدنا القيمة في الشجرة */
            return i + 1;  }
    }
    return 0;  /**إذا لم يتم العثور على القيمة في أي شجرة0 */
}
int getTreeSize(tree arber) {
    /*الحجم  (العقدة الحالية)هو 1 + حجم العقد في الفرع الأيسر + حجم العقد في الفرع الأيمن*/
    return 1 + getTreeSize(arber->left) + getTreeSize(arber->right);
}
/*الة لتحديد الشجرة التي تحتوي على أقل عدد من العقد*/
int findTreeWithMinSize(tree* arrytree, int N) {
    int minSizeIndex = -1;
    int minSize = INT_MAX;
    
    for (int i = 0; i < N; i++) {
        int treeSize = getTreeSize(arrytree[i]); /** حساب حجم الشجرة */
        if (treeSize < minSize) {/*إذا كانت الشجرة الحالية أصغر*/
            minSize = treeSize;
            minSizeIndex = i;
        }
    }

    return minSizeIndex;
}
/*دالة لتحديد الشجرة التي تحتوي على أكبر عدد من العقد*/
int findTreeWithMaxSize(tree* arrytree, int N) {
    int maxSizeIndex = -1;
    int maxSize = -1;
    
    for (int i = 0; i < N; i++) {
        int treeSize = getTreeSize(arrytree[i]);
        if (treeSize > maxSize) {
            maxSize = treeSize;
            maxSizeIndex = i;
        }
    }

    return maxSizeIndex;
}
//** دالة للحصول على الحد الأدنى في شجرة واحدة */
int findMinValue(tree arber) {
  
    while (arber->left != NULL) {
        arber = arber->left; 
    }
    return arber->value; /* أصغر قيمة تكون في أقصى اليسار*/
}
//** دالة للحصول على الحد الأقصى في شجرة واحدة */
int findMaxValue(tree arber) {
   
    while (arber->right != NULL) {
        arber = arber->right; 
    }
    return arber->value; /*أكبر قيمة تكون في أقصى اليمين*/ 
}
void menu (){
    printf("\n____Choose what you want to do____\n");
    printf("1.Add a value to a specific tree\n");
    printf("2.Add a random value to a tree\n");
    printf("4.Order the roots of a tree\n");
    printf("5.Search for a specific value within a specific tree\n");
    printf("6.Search for a value in all trees\n");
    printf("7.Determine the tree with the largest number of nodes\n");
    printf("8.Determine the tree with the smallest number of nodes\n");
    printf("9.Determine the tree that contains the node with the minimum value\n");
     printf("10.Determine the tree that contains the node with the maximum value\n");
     printf("11.Display tree in pre-order\n");
     printf("12.Display tree in intermediate order\n");
     printf("13.Display tree in post-order\n");
     printf("14.Display tree in branching order\n");
     printf("15. Exit\n");
}
// دالة الفرز بالدمج
void  par_fusion(tree* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  /*تحديد المنتصف*/ 

        /*فرز الجزء الايسر*/ 
        mergeSort(array, left, mid);
        
        /*فرز الجزء الأيمن*/ 
        mergeSort(array, mid + 1, right);

        /* دمج الجزئين بعد فرزهما*/ 
        merge(array, left, mid, right);
    }
}
int main() {
    int n; // عدد الأشجار
    printf("Enter the number of trees: ");
    scanf("%d", &n);

    // تهيئة مصفوفة الأشجار
    tree* arrytree = Initializing_the_Tree_Table(n);
    if (arrytree == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

  menu();
    int choice;
   while (choice != 15){
        menu();  // عرض القائمة
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
            case 2: {
                int treeIndex;
                printf("Enter the tree index (0 to %d) to add random value: ", n - 1);
                scanf("%d", &treeIndex);
                int randomValue = rand() % 1000+1;
                Ajout_d_une_Valeur_à_une_Case(arrytree, treeIndex, randomValue, n);
                break;
            }
            case 4: {
                int treeIndex;
                printf("Enter the tree index (0 to %d) to order roots: ", n - 1);
                scanf("%d", &treeIndex);
                printf("in : 1.par bulles\n2.par sélection\n 3. par fusion\n enter you choise: ");
                int h,max;scanf("%d",&h);
                if (h==1){

                printf("\nAscending=1 °°° Descending=0\n");
                scanf("%d",&max);
                    par_bulles(arrytree,n,max);}
                else if (h==2) {
                printf("\nAscending=1 °°° Descending=0\n");
                scanf("%d",&max);
                par_sélection(arrytree,n,max);
                }
                else{
                    par_fusion(arrytree,0,n-1);
                }
                break;
            }
            case 5: {
                int treeIndex, value;
                printf("Enter the tree index (0 to %d) and value to search: ", n - 1);
                scanf("%d %d", &treeIndex, &value);
                if (Recherche_dans_un_Arbr_d_un_Case(arrytree[treeIndex], value)) {
                    printf("Value %d found in tree %d\n", value, treeIndex);
                } else {
                    printf("Value %d not found in tree %d\n", value, treeIndex);
                }
                break;
            }
            case 6: {
                int value;
                printf("Enter the value to search in all trees: ");
                scanf("%d", &value);
                int foundIndex = Recherche_Globale(arrytree, n, value);
                if (foundIndex) {
                    printf("Value %d found in tree %d\n", value, foundIndex);
                } else {
                    printf("Value %d not found in any tree\n", value);
                }
                break;
            }
            case 7: {
                int treeIndex = findTreeWithMaxSize(arrytree, n);
                printf("Tree with max size: %d\n", treeIndex);
                break;
            }
            case 8: {
                int treeIndex = findTreeWithMinSize(arrytree, n);
                printf("Tree with min size: %d\n", treeIndex);
                break;
            }
            case 9: {
                int treeIndex = findMinValue(arrytree);
                printf("Tree with global min value: %d\n", treeIndex);
                break;
            }
            case 10: {
                int treeIndex = findMaxValue(arrytree);
                printf("Tree with global max value: %d\n", treeIndex);
                break;
            }
            case 11: {
                int treeIndex;
                printf("Enter the tree index (0 to %d) to display in pre-order: ", n - 1);
                scanf("%d", &treeIndex);
               Préfixe(arrytree[treeIndex]);
                printf("\n");
                break;
            }
            case 12: {
                int treeIndex;
                printf("Enter the tree index (0 to %d) to display in in-order: ", n - 1);
                scanf("%d", &treeIndex);
               Infixe(arrytree[treeIndex]);
                printf("\n");
                break;
            }
            case 13: {
                int treeIndex;
                printf("Enter the tree index (0 to %d) to display in post-order: ", n - 1);
                scanf("%d", &treeIndex);
               Postfixe(arrytree[treeIndex]);
                printf("\n");
                break;
            }
            case 14: {
                int treeIndex;
                printf("Enter the tree index (0 to %d) to display in branching order: ", n - 1);
                scanf("%d", &treeIndex);
                print(arrytree[treeIndex], 0); /*العرض بشكل هرمي*/  
                break;
            }
            
            case 15:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } ;

    /*تحرير الذاكرة*/ 
    freee(arrytree, n);

    return 0;
}
