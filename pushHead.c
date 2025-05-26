#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *berikut;
} *head , *tail, *current,*delete,*beforeCurrent;

void pushHead(int dataPush)
{
    current=(struct node*)malloc(sizeof(struct node)); //pesan ruang memori
    current->data=dataPush;
    if (head==NULL)
        head=tail=current;
    else    
    {
        current->berikut=head;
        head=current;
        tail->berikut=NULL;
    }
}

void hapusNode(int Lokasi)
{
    if (Lokasi==1)  //HapusDepan
    {
        if (head==NULL)
            printf("Tidak ada Node\n");
        else
        {
            current=head;
            delete=current;
            current=current->berikut;
            head=current;
            free(delete);

        }
    }
    else
    if (Lokasi==0) //hapus Belakang
        if (head==NULL)
            printf("Tidak ada Node\n");
        else
        {
            current=tail;
            delete=current;
            beforeCurrent=head;
            while (beforeCurrent->berikut!=current)
            {
                beforeCurrent=beforeCurrent->berikut;
            }
            tail=beforeCurrent;
            free(delete);
            tail->berikut=NULL;
        }
    
        
}


void pushTail(int dataTail)
{
    current=(struct node*)malloc(sizeof(struct node));
    current->data=dataTail;
    if (head==NULL)
        head=current=tail;
    else
    {
        tail->berikut=current;
        tail=current;
        tail->berikut=NULL;
    }
}
void viewLinkList()
{
    current=head;
    printf("Head -> ");
    while  (current!=NULL)
    {
        printf("%d -> ",current->data);
        current=current->berikut;
    }
    printf("NULL");
}


void main()
{
    int pilih,pushData;
    while (pilih<7)
    {
    printf("Mengisi data ke Link List \n");
    printf("------------------------- \n\n");
    printf("pilih \n");
    printf("-------\n");
    printf("1. isi head\n");
    printf("2. isi Tail\n");
    printf("3. hapus Depan\n");
    printf("4. hapus Belakang\n");
    printf("5. Antrian - Queue\n");
    printf("6. Tumpukan - Stack\n ");
    printf(" Pilih (1-6) : ");
    scanf("%d",&pilih);
    if (pilih==1)
      {
        printf("data entry : ");
        scanf("%d",&pushData);
        pushHead(pushData);    
      }
    else
     if (pilih==2)
     {
        printf("data entry : ");
        scanf("%d",&pushData);
        pushTail(pushData);
     }
    else
     if (pilih==3)
     {
        hapusNode(1);
     }
    else
     if (pilih==4)
     {
        hapusNode(0);
     }
    else
    if (pilih==5)
    {
        if (head==NULL)
        {
            printf("data entry : ");
            scanf("%d",&pushData);
            pushTail(pushData);    
        }
        else
        {
            int qPilih;
            printf("Hapus Antrian depan (0)/Tambah Antrian (1) : ");
            scanf(" %d",&qPilih);
            if (qPilih==1)
            {
                printf("data entry : ");
                scanf("%d",&pushData);
                pushTail(pushData);    
            }
            else if (qPilih==0)
            {
                hapusNode(1);
            }
        }
        
    }
    else
    if (pilih==6)
    {
        int sPilih;
        printf("Push=1/pop=0 : ");
        scanf("%d",&sPilih);
        if (sPilih==1)
        {
            printf("data entry : ");
            scanf("%d",&pushData);
            pushHead(pushData);
        }
        else
        if (sPilih==0)
        {
            hapusNode(1);
        }
           
    }
    viewLinkList();
    printf("\n\n");
    }
    
}
    
