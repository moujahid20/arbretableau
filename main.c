#include <stdio.h>
#include <stdlib.h>
#define maxelem 100

/// structure d'une neoude
typedef struct ar
{
    int elem;//l'element de noeud
    int fgch;//indice du fils gouche
    int fdrt;//indice du fils droite
    int pere;//indice du pere
}noeud;

/// structure d'une arbre
typedef struct
{
    noeud *tab[maxelem];// tableau des neouds
    int rac;// indice du racine de tableau
    int nbrelem;//nbr des elements
}ARB;

/// fct pour initialiser l'arbre
int initialiser_arb(ARB *arb)
{
    if(!arb) return 0;// erreur allocation de la memoire
    arb->rac=arb->nbrelem=0;//initialiser le racine et nbrelem par 0
    arb->tab[arb->rac]=NULL;//initialiser  l'arbre par NULL
    return 1;
}

/// fonction pour creer une neoude
ARB *creerneoud(int elem)
{
    //allouer une espace memoire
    noeud *nod=(noeud*)malloc(sizeof(noeud));
    //tester si l'allocation passe bien
    if(!nod) exit(-1);
    //initialiser les indeces des fils et pere par 0
    nod->fdrt=nod->fgch=nod->pere=0;
    nod->elem=elem;
    return(ARB*)nod;
}

///insertion d'un element dans une arbre
//ind c'est l'indice de l'arbre
int inserer_arb(ARB *arbre,int ind,noeud *N)
{
    //tester si l'arbre n'existe pas
    if(!arbre) return -1;
    //tester si l'arbre est vide
    if(!arbre->tab[ind])
    {
        //inserer le noeud comme indice d'arbre
        arbre->tab[++arbre->rac]=N;
        //augmenter le nbr des element
        arbre->nbrelem++;
        return 1;
    }
    else{
    //tester si l'element de noeud est plus petit que l'indece
        if(arbre->tab[ind]->elem > N->elem)
        {
            //tester si le fils gouche de l'indece NULL
            if(!arbre->tab[arbre->tab[ind]->fgch])
            {
                //tester si le tableau est plien
                if(maxelem<=arbre->nbrelem) return 0;
                //inserer la noeud a la gouche de l'indice
                //augmenter le nbr des element
                arbre->tab[ind]->fgch=++arbre->nbrelem;
                N->pere=ind;
                arbre->tab[arbre->nbrelem]=N;
                return 1;
            }
            else
                //nous appelons la fct pour inserer l'element a une position gouche
                return(int)inserer_arb(arbre,arbre->tab[ind]->fgch,N);
        }
        else
        {
        //tester si l'element de noeud est plus petit que l'indece
            if(!arbre->tab[arbre->tab[ind]->fdrt])
            {
            //tester si le fils gouche de l'indece NULL
                if(maxelem<=(arbre->nbrelem+1)) return 0;
                //inserer la noeud a la droite de l'indice
                //augmenter le nbr des element
                arbre->tab[ind]->fdrt=(++arbre->nbrelem);
                N->pere=ind;
                arbre->tab[arbre->nbrelem]=N;
            }
            else
                //nous appelons la fct pour inserer l'element a une position droite
                return(int)inserer_arb(arbre,arbre->tab[ind]->fdrt,N);
        }

    }

}

// fct pour afficher l'arbre (infixe)
void infixe(ARB *arbre,int ind)
{
    //tester si l'arbre n'est pas vide
    if(arbre->tab[ind])
    {
        //appeler la fct infixe pour passer a la gouche de l'arbre
        infixe(arbre,arbre->tab[ind]->fgch);
        //afficher l'elemnt trouve
        printf("%d->",arbre->tab[ind]->elem);
        //appeler la fct infixe pour passer a la droite de l'arbre
        infixe(arbre,arbre->tab[ind]->fdrt);
    }
}

/// fct pour afficher l'arbre (postefixe)
void postefixe(ARB *arbre,int ind)
{
    //tester si l'arbre n'est pas vide
    if(arbre->tab[ind])
    {
        //appeler la fct infixe pour passer a la gouche de l'arbre
        postefixe(arbre,arbre->tab[ind]->fgch);
        //appeler la fct infixe pour passer a la droite de l'arbre
        postefixe(arbre,arbre->tab[ind]->fdrt);
        //afficher l'elemnt trouve
        printf("%d->",arbre->tab[ind]->elem);
    }
}
// fct pour afficher l'arbre (prefixe)
void prefixe(ARB *arbre,int ind)
{
    //tester si l'arbre n'est pas vide
    if(arbre->tab[ind])
    {
        //afficher l'elemnt trouver
        printf("%d->",arbre->tab[ind]->elem);
        //appeler la fct infixe pour passer a la gouche de l'arbre
        prefixe(arbre,arbre->tab[ind]->fgch);
        //appeler la fct infixe pour passer a la droite de l'arbre
        prefixe(arbre,arbre->tab[ind]->fdrt);
    }
}

/// fonction de recherche
int recherche(ARB *arb,int ind,int rech,int *indece)
{
    //tester si l'arbre n'est pas vide
    if(arb->tab[ind])
    {
        // tester si l'element a recherche est le recine
        if(rech==arb->tab[ind]->elem)
        {
            //prondre l'indice d'element
            *indece=ind;
            //return 1 (l'element existe)
            return 1;
        }
        //sinon appeler la fct recherche pour passer a la gouche de l'arbre
        if(recherche(arb,arb->tab[ind]->fgch,rech,indece)) return 1;
        //appeler la fct recherche pour passer a la droite de l'arbre
        if(recherche(arb,arb->tab[ind]->fdrt,rech,indece)) return 1;
        //si n'existe pas return 0
        return 0;
    }
}
ARB *suppression(ARB *arbre,int ind,int elem_supp)
{
    int ind_elem;//pour l'indice de l'element a supprimer
    int i;//pour mettre l'indice des fils
    //tester si l'element existe
    if(recherche(arbre,ind,elem_supp,&ind_elem))
    {
        //tester si l'arbre contient un seule element
        //attention d'apres la fct recheche c'element est la meme supp_elem
        if(!arbre->tab[ind]->fdrt && !arbre->tab[ind]->fgch )
        //tester si l'initialisation (pour vider) passe bien
                    if(initialiser_arb(arbre))  return arbre;
        //tester si le noeud le noeud supp est un feuille
        if(!arbre->tab[ind_elem]->fdrt && !arbre->tab[ind_elem]->fgch)
        {
            //tester si le fils droite du pere est le noeud supp
            if(arbre->tab[arbre->tab[ind_elem]->pere]->fdrt==ind_elem)
                    //initialiser l'indice de fils droite du pere
                    arbre->tab[arbre->tab[ind_elem]->pere]->fdrt=0;
            else
                //sinon initialiser l'indice de fils droite du pere
                arbre->tab[arbre->tab[ind_elem]->pere]->fgch=0;
            //initialiser la noeud supp
            arbre->tab[ind_elem]=NULL;
            //decrimenter le nbr des elements
            arbre->nbrelem--;
            return arbre;
        }
        //tester si la noeud sup n'a pas de fils gouche
        if(!arbre->tab[ind_elem]->fgch)
        {
            //mettre dans i l'indice de fils droite
            i=arbre->tab[ind_elem]->fdrt;
            //boucle pour passer a le noeud le plus gouche
            while(arbre->tab[i]->fgch)
                 i=arbre->tab[i]->fgch;
            //tester si l'indice du fils droite du pere du noeu i est i
            if(arbre->tab[arbre->tab[i]->pere]->fdrt==i)
                /*mettre dans l'indice du fils droite du pere du noeud i
                  le fils droite du noeud i*/
                    arbre->tab[arbre->tab[i]->pere]->fdrt=arbre->tab[i]->fdrt;
            else
            /*sinon mettre dans l'indice du fils gouche du pere du noeud i
            l'indice du fils droite du noeud i*/
                arbre->tab[arbre->tab[i]->pere]->fgch=arbre->tab[i]->fdrt;
            //mettre l'indice de l'element i dans la noeud de l'elem supp
            arbre->tab[ind_elem]->elem=arbre->tab[i]->elem;
            //supprimer la noeud i
            arbre->tab[i]=NULL;
            //decrimenter le nbr des elements
            arbre->nbrelem--;
            return arbre;
        }
        //sinon mettre dans i l'indice de fils gouche
        i=arbre->tab[ind_elem]->fgch;
        //boucle pour passer a le noeud le plus droite
        while(arbre->tab[i]->fdrt)
            i=arbre->tab[i]->fdrt;
        //tester si l'indice du fils gouche du pere du noeud i est i
        if(arbre->tab[arbre->tab[i]->pere]->fgch==i)
            /*mettre dans l'indice du fils gouche du pere du noeud i
                  le fils droite du noeud i*/
            arbre->tab[arbre->tab[i]->pere]->fgch=arbre->tab[i]->fgch;

        else
            /*sinon mettre dans l'indice du fils droite du pere du noeud i
          le fils droite du noeud i*/
                arbre->tab[arbre->tab[i]->pere]->fdrt=arbre->tab[i]->fgch;
        //mettre l'indice de l'element i dans la noeud de l'elem supp
        arbre->tab[ind_elem]->elem=arbre->tab[i]->elem;
        //supprimer la noeud i
        arbre->tab[i]=NULL;
        //decrimenter le nbr des elements
        arbre->nbrelem--;
        return arbre;
    }
}

/// fct pour calculer la taille d'une arbre
int TArb(ARB *Arb, int id)
{
    //si l'arbre n'existe pas
    if (!Arb) return ((int)-1);
    //si l'arbre est vide
    if (!id) return ((int)0);
    //return la somme de la taille l'arbre gouche et l'arbre droite
    return ((int)1+TArb(Arb,Arb->tab[id]->fdrt)+TArb(Arb,Arb->tab[id]->fgch));
}
// fct pou afficher l'arbre horizontalement
// n c'est la nombre des tabulation
void AffichageHorizontal(ARB *Arb, int id, int n)
{
    // si l'arbre n'est pas vide
    if (id != 0)
     {
    // nous appelons la fct pour l'arbre goucheet on augmentons le nbr des tabulations
            AffichageHorizontal(Arb,Arb->tab[id]->fgch,n+1);
            printf("\n");
            //nous affichons le nmbr des tabulation
            for (int i = 0; i < n; i++) printf("\t");
            //nous affichons l'element
            printf("%d",Arb->tab[id]->elem);
    // nous appelons la fct pour l'arbre droite on augmentons le nbr de tabulation
            AffichageHorizontal(Arb,Arb->tab[id]->fdrt,n+1);
    }
}
//fct pour determiner le max d'une arbre
int MaxArbre(ARB *arbre,int ind)
{
    if(ind)
    {
        // on passe jusqu'a le noeud le plus droite
        MaxArbre(arbre,arbre->tab[ind]->fdrt);
        //nous affichons l'element
        if(!arbre->tab[ind]->fdrt)
            printf("\n le maximun est: %d",arbre->tab[ind]->elem);

    }
}
//fct pour determiner le min d'une arbre
int minArbre(ARB *arbre,int ind )
{
    if(ind)
    {
        // on passe jusqu'a le noeud le plus gouche
        minArbre(arbre,arbre->tab[ind]->fgch);
        //nous affichons l'element
        if(!arbre->tab[ind]->fgch)
            printf("\n le minimun est: %d",arbre->tab[ind]->elem);
    }
}
int main()
{

     ARB *arb=(ARB*)malloc(sizeof(ARB));
     if(initialiser_arb(arb));
     int j,k,i,d,b;
     noeud *nd;
     printf("\n\n l'insertion des elements : 6  \n");
     nd=creerneoud(6);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 3  \n");
     nd=creerneoud(3);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 0  \n");
     nd=creerneoud(0);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 5  \n");
     nd=creerneoud(5);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 4  \n");
     nd=creerneoud(4);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 5 \n");
     nd=creerneoud(5);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 8  \n");
     nd=creerneoud(8);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 7  \n");
     nd=creerneoud(7);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 8 \n");
     nd=creerneoud(8);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
     printf("\n\n l'insertion des elements : 11 \n");
     nd=creerneoud(11);
     if(inserer_arb(arb,arb->rac,nd)==1);
     AffichageHorizontal(arb,arb->rac,3);
       printf("\n\t**************************************************");
     printf("\n l'affichage infixe est : \n");
     infixe(arb,arb->rac);
     printf("\n l'affichage prefixe est : \n");
     prefixe(arb,arb->rac);
     printf("\n l'affichage postefixe est : \n");
     postefixe(arb,arb->rac);
       printf("\n\t**************************************************");
     printf("\n entrer l'element a recheche: ");
     scanf("%d",&k);
     if(recherche(arb,arb->rac,k,&d)) printf("\n l'element existe et sa position :%d \n",d);
     else printf("\n l'element n'est existe pas ");
       printf("\n\t**************************************************");
     printf("\n la suppression de l'element %d: \n",k);
     arb=suppression(arb,arb->rac,k);
    AffichageHorizontal(arb,arb->rac,3);
    printf("\n\t**************************************************");
    printf("\n l'affichage infixe est : \n");
     infixe(arb,arb->rac);
     printf("\n la taille est: %d",TArb(arb,arb->rac));
     minArbre(arb,arb->rac);
     MaxArbre(arb,arb->rac);


     return 1;
}
