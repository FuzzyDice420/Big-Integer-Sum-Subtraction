#include <iostream>

using namespace std;

/**
Tema 18. numere intregi mari (reprezentate ca indicator de semn si liste dinamice de cifre,
incepand cu cifra unitatilor - vor fi afisate uzual, incepand cu cifra dominanta si incheind
cu cifra unitatilor):

o clasa numar intreg mare sa contina metode pentru supraincarcarea operatorilor <<
si >> pentru iesiri si intrari, precum si pentru calculul: sumei a doua numere intregi
mari, prin supraincarcarea operatorului +, diferentei dintre doua numere intregi
mari, prin supraincarcarea operatorului -, produsului dintre doua numere intregi
mari, prin supraincarcarea operatorului *, maximului dintre valorile absolute a
doua numere intregi mari; impartirea si restul a doua numere intregi mari prin
surpaincarcarea operatorilor / si % precum si aruncarea unei exceptii daca se
realizeaza impartirea la 0; metoda pentru calculul partii intregi a radicinii patrate a
modului numarului mare.

o sa se creeze o clasa vector de numere intregi mari, prietena a clasei numar intreg
mare, care sa contina metode pentru: supraincarcarea operatorilor << si >>,
folosind metodele de supraincare pentru << si >> din clasa numar intreg mare;
produs scalar dintre doi vectori de numere intregi mari cu acelasi numar de
elemente, care sa supraincarce operatorul * si sa foloseasca produsul si suma din
clasa numar intreg mare; calculul valorii absolute maxime dintr-un vector de
numere intregi mari, folosind maximul dintre valorile absolute a doua numere
intregi mari preluat din clasa numar intreg mare;

o Clasele trebuie implementate folosind alocare dinamica
**/

class number{
    int digit;
    number *next;
    friend class bigInt;
};

class bigInt{
    number *first, *last;
    char sign;
public:
    bigInt(){ first = NULL; last = NULL;}
    /*bigInt(const bigInt &ob){

    }*/
    void add_final();
    void create();
    void afisare();
    void reverseList();
    int len();
    bigInt addition(bigInt &A, bigInt &B);
    bigInt subtract(bigInt &A, bigInt &B);
    friend istream& operator >>(istream &in, bigInt &A);
    friend ostream& operator <<(ostream &out, bigInt &A);
    friend bigInt operator +(bigInt &A, bigInt &B);
    friend bigInt operator -(bigInt &A, bigInt &B);
    bigInt operator *(bigInt &A);
    int operator /(bigInt &A);
    bigInt operator %(bigInt &A);
    void operator =(const bigInt& ob);
    int operator ==(bigInt &A);
    int operator !=(bigInt &A);
    int operator <(bigInt &A);
    friend class vectorInt;
    /*~bigInt(){
        number *p, *old;
        for(p = first; p->next != NULL; p = first->next){
            old = p->next;
            p->next = old->next;
            delete old;
        }
    }*/
};

class vectorInt{
    int dim;
    bigInt *v;
public:
    vectorInt(){ dim = 0; v = NULL;}
    void init(int n);
    void add(bigInt &A);
    void afisare(int n);
    void vsort(int n);
};

void bigInt::add_final(){
    number *p;
    p = new number [1];
    do{
        cin >> p->digit;
    }while(p->digit < 0 || p->digit > 9);
    p->next = NULL;
    if(first == NULL){
        first = p;
        last = p;
    }
    else {
        last->next = p;
        last = p;
    }
}

void bigInt::afisare(){
    number *p;
    cout << "Numarul intreg mare este: ";
    cout << sign << " ";
    for(p = first; p != NULL; p = p->next){
        cout << p->digit << " ";
    }
    cout << endl;
}

void bigInt::create(){
    int n;
    cout << "Numar de cifre: ";
    cin >> n;
    cout << "Semn: ";
    cin >> sign;
    cout << "Introduceti numerele: " << endl;
    for(int i = 0; i < n; i++){
        //add_final(first, last);
        add_final();
    }
}

void bigInt::reverseList(){ // inverseaza ordinea listei
    number *p, *c, *n; // previous, current, next
    p = NULL;
    last = first;
    for(c = first; c != NULL; c = n){
        n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    first = p;
}

int bigInt::len(){ // calculeaza numarul de elemente al listei
    number *c;
    int k = 0;
    for(c = first; c != NULL; c = c->next){
        k++;
    }
    return k;
}

void vectorInt::init(int n){
    v = new bigInt [n];
}

void vectorInt::add(bigInt &A){
    v[dim] = A;
    dim++;
}

void vectorInt::afisare(int n){
    for(int i = 0; i < n; i++){
        cout << v[i];
    }
}

void vectorInt::vsort(int n){
    bigInt aux;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(v[j + 1] < v[j]){
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

istream& operator >>(istream& in, bigInt &A){
    A.create();
    return in;
}

ostream& operator <<(ostream & out, bigInt &A){
    A.afisare();
    return out;
}

void bigInt::operator=(const bigInt &ob){
    number *p, *c;
    for(c = ob.first; c != NULL;  c = c->next){
        p = new number [1];
        p->next = NULL;
        p->digit = c->digit;
        if(first == NULL){
            first = p;
            last = p;
        }
        else{
            last->next = p;
            last = p;
        }
        p = p->next;
    }
    this->sign = ob.sign;
}

bigInt operator + (bigInt &A, bigInt &B){
    bigInt add, sub;
    if(A.sign == '+' && B.sign == '+'){
        return A.addition(B, A);
    }
    else if(A.sign == '-' && B.sign == '-'){
        add = A.addition(B, A);
        add.sign = '-';
        return add;
    }
    else if(B.sign == '-' && A.sign == '+'){
        if(B < A){
            sub = A.subtract(A, B);
            sub.sign = '+';
            return sub;
        }
        else {
            sub = A.subtract(B, A);
            sub.sign = '-';
            return sub;
        }
    }
    else if(B.sign == '+' && A.sign == '-'){
        if(B < A){
             sub = A.subtract(A, B);
            sub.sign = '-';
            return sub;
        }
        else {
             sub = A.subtract(B, A);
            sub.sign = '+';
            return sub;
        }
    }
}

bigInt bigInt::addition(bigInt &B, bigInt &A){
    int maxi, mini, l1, l2, carry = 0;
    bigInt add;
    number *p, *a1, *a2;
    l1 = A.len();
    l2 = B.len();
    maxi = (l1 < l2) ? l2 : l1;
    mini = (l1 < l2) ? l1 : l2;
    //cout << endl << maxi << " " << mini << endl;
    if(maxi == l1){ // pune zerouri la coada listei pentru adunare
        B.reverseList();
        for(int i = 0; i < maxi - mini; i++){
            p = new number [1];
            p->next = NULL;
            p->digit = 0;
            B.last->next = p;
            B.last = p;
        }
        B.reverseList();
    }
    else if(maxi == l2){ // pune zerouri la coada listei pentru adunare
        A.reverseList();
        for(int i = 0; i < maxi - mini; i++){
            p = new number [1];
            p->next = NULL;
            p->digit = 0;
            A.last->next = p;
            A.last = p;
        }
        A.reverseList();
    }
    B.reverseList();
    A.reverseList();
    cout << B << endl;
    cout << A << endl;
    // crearea listei in care se salveaza adunarea
    for(int i = 0; i < maxi; i++){
        p = new number [1];
        p->next = NULL;
        p->digit = 0;
        if(add.first == NULL){
            add.first = p;
            add.last = p;
        }
        else{
            add.last->next = p;
            add.last = p;
        }
    }
    p = add.first;
    a1 = B.first;
    a2 = A.first;
    while(p != NULL){ // adunarea
        p->digit += a1->digit + a2->digit;
        if(p->digit > 9){
            p->digit = p->digit % 10;
            if(p->next == NULL){
                carry = 1;
                break;
            }
            (p->next->digit)++;
        }
        p = p->next;
        a1 = a1->next;
        a2 = a2->next;
    }
    if(carry == 1){
        p = new number [1];
        p->next = NULL;
        p->digit = 1;
        add.last->next = p;
        add.last = p;
    }
    add.reverseList(); // inverseaza lista care este exact adunarea celor doua
    return add;
}

bigInt operator - (bigInt &A, bigInt &B){
    bigInt sub;
    if(B.sign == '+' && A.sign == '+') {
        if(B < A){
            sub = A.subtract(A, B);
            sub.sign = '+';
            return sub;
        }
        else {
            sub = A.subtract(B, A);
            sub.sign = '-';
            return sub;
        }
    }
    else if(B.sign == '-' && A.sign == '+'){
        sub = A.addition(B, A);
        sub.sign = '-';
        return sub;
    }
    else if(B.sign == '+' && A.sign == '-'){
        sub = A.addition(B, A);
        sub.sign = '+';
        return sub;
    }
}

bigInt bigInt::subtract(bigInt &B, bigInt &A){
    bigInt sub;
    int maxi, mini, l1, l2;
    number *p, *s1, *s2;
    l1 = B.len();
    l2 = A.len();
    maxi = (l1 < l2) ? l2 : l1;
    mini = (l1 < l2) ? l1 : l2;
    B.reverseList();
    A.reverseList();
    if(maxi == l2){
        for(int i = 0; i < maxi - mini; i++){
            p = new number [1];
            p->next = NULL;
            p->digit = 0;
            B.last->next = p;
            B.last = p;
        }
    }
    else if(maxi == l1){
        for(int i = 0; i < maxi - mini; i++){
            p = new number [1];
            p->next = NULL;
            p->digit = 0;
            A.last->next = p;
            A.last = p;
        }
    }
    for(int i = 0; i < maxi; i++){
        p = new number [1];
        p->next = NULL;
        p->digit = 0;
        if(sub.first == NULL){
            sub.first = p;
            sub.last = p;
        }
        else{
            sub.last->next = p;
            sub.last = p;
        }
    }
    p = sub.first;
    s1 = B.first;
    s2 = A.first;
    while(p != NULL){
        if(s1->digit < s2->digit){ // daca scad din ceva mai mic ceva mai mare, ma imprumut de la urmatorul element
            if(s1->digit == 0){ // daca ma imprumut de la un element egal cu 0, continui cautarea pt imprumutare si in loc de 0 vine 9
                (s1->next->digit)--;
                s1->digit = 9;
            }
            else {
                (s1->next->digit)--; // ma imprumut cu o unitate
                s1->digit += 10;
            }
        }
        p->digit += s1->digit - s2->digit;
        //cout << p->digit << endl;
        p = p->next;
        s1 = s1->next;
        s2 = s2->next;
    }
    sub.reverseList();
    return sub;
}

int bigInt::operator /(bigInt &A){
    bigInt div;
    int k = 0;
    if(A.first->digit == 0){
        cout << "Nu se poate imparti la 0!" << endl;
        return -1;
    }
    div = *this - A;
    cout << div;
    while((A < div) == 1){
        div = div - A;
        k++;
    }
    return k + 1;
}

int bigInt::operator ==(bigInt &A){
    number *p1, *p2;
    p1 = this->first;
    p2 = A.first;
    if(this->len() != A.len()){
        return 0;
    }
    while(p1 != NULL){
        if(p1->digit != p2->digit){
            return 0;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return 1;
}

int bigInt::operator !=(bigInt &A){
    number *p1, *p2;
    p1 = this->first;
    p2 = A.first;
    if(this->len() != A.len()){
        return 1;
    }
    while(p1 != NULL){
        if(p1->digit != p2->digit){
            return 1;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return 0;
}

int bigInt::operator <(bigInt &A){
    number *p1, *p2;
    p1 = this->first;
    p2 = A.first;
    if(this->len() < A.len()){
        return 1;
    }
    while(p1 != NULL){
        if(p1->digit > p2->digit){
            return 0;
        }
        else if(p1->digit < p2->digit){
            return 1;
        }
        else{
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return 1;
}

int main()
{
    bigInt A, B, add, sub;
    vectorInt v;
    int n;
    cin >> A;
    cout << A;
    //cout << A;
    //bigInt B(A);
    cin >> B;
    cout << B;
    sub = A - B;
    cout << sub;
    //n = A / B;
    //cout << n;
    //cout << "Nr de elemente al vectorului: ";
    //cin >> n;
    //add = A + B;
    //cout << add;
    //sub = A - B;
    //cout << sub;
    //if((A < B) == 1) cout << "A mai mic ca B";
    //v.init(n);
    //v.add(A);
    //v.add(B);
    //v.afisare(n);
    //v.vsort(n);
    //v.afisare(n);
    return 0;
}
