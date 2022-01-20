#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
//Fatma Gül Yýldýrým 190201017
//Kerem Karataþ 190201076
void sekli_goruntule();
void yeniden_boyutlandir(int,int );
void koordinati_birimlere_ayir();
void koordinata_sayi_yazdir();
void sayfayi_karelere_bol();
void koordinat_ciz_ok_ciz();
void dosyadaki_nokta_adedi(int *);
void dosyadan_oku_ve_noktalari_ciz(int [][2],int);
void yaricap_merkezx_merkezy_bul_yaricapi_merkezi_goster(float *,float *,float *,int [][2],int);
void cemberi_ciz(float,float,float);
void diziyi_sirala(int [][2],int );

int main(int argc, char ** argv)
{
    //GLUT kitaplýðýný ilklendirdik.
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(200,0);
    glutCreateWindow("OpenGL Dersleri");
    glutDisplayFunc(sekli_goruntule);
    glutReshapeFunc(yeniden_boyutlandir);
    glutMainLoop();
    return 0;

}


void sekli_goruntule()
{
    glClear(GL_COLOR_BUFFER_BIT);
    koordinati_birimlere_ayir();
    koordinata_sayi_yazdir();
    sayfayi_karelere_bol();
    koordinat_ciz_ok_ciz();
    int adet=0;
    dosyadaki_nokta_adedi(&adet);
    int dizi[adet][2];
    dosyadan_oku_ve_noktalari_ciz(dizi,adet);
    float merkezx,merkezy,r;
    yaricap_merkezx_merkezy_bul_yaricapi_merkezi_goster(&r,&merkezx,&merkezy,dizi,adet);
    cemberi_ciz(merkezx,merkezy,r);
    diziyi_sirala(dizi,adet);
    float X,Y;
    glColor3f(0,1,0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
     int d,m,g;
    for(int i=0; i<adet; i+=3)
    {
        for( float a=0; a<=1; a+=0.001)
        {
           float b =1-a;
            d=i+1;
            m=i+2;
            g=i+3;
            if(i==adet-1)
            {
                d=i;
                m=i;
                g=i;
            }
            if(i==adet-2)
            {
                m=i+1;
                g=i+1;
            }
            if(i==adet-3)
            {
                g=i+2;
            }

            X =(dizi[i][0]*b*b*b+dizi[d][0]*(6*a*b*b)+dizi[m][0]*(3*a*a*b)+dizi[g][0]*a*a*a)/(3*a*a*a-6*a*a+3*a+1);
            Y =(dizi[i][1]*b*b*b+dizi[d][1]*(6*a*b*b)+dizi[m][1]*(3*a*a*b)+dizi[g][1]*a*a*a)/(3*a*a*a-6*a*a+3*a+1);

            glVertex2f(X,Y);

        }
    }
    glEnd();
    glFlush();
    glutSwapBuffers();
    printf("merkez::(%f,%f)\n",merkezx,merkezy);
    printf("yaricap::%f\n",r);
}

void yeniden_boyutlandir(int w,int h)
{
    //Burada koordinatýmýzý -30,30 olarak ayarladýk.
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
  
    if (w <= h)
        glOrtho(-30.0, 30.0, -30.0*(GLfloat)h/(GLfloat)w,
                30.0*(GLfloat)h/(GLfloat)w, -30.0, 30.0);
    else
        glOrtho(-30.0*(GLfloat)w/(GLfloat)h,
                30.0*(GLfloat)w/(GLfloat)h, -30.0, 30.0, -30.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
  
}

void koordinati_birimlere_ayir()
{
    glColor3f(0,0,1);
    float a=1.0,b=1.0;
    for(int i =1; i<30; i++)
    {

        glRasterPos2f(a,0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'|');

        glRasterPos2f(0,-b);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'_');
        glRasterPos2f(-0.5,-b);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'_');


        glRasterPos2f(0,b);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'_');
        glRasterPos2f(-0.5,b);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'_');

        glRasterPos2f(-a,0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'|');

        a+=1;
        b+=1;

    }
}

void koordinata_sayi_yazdir()
{
    glColor3f(1,0,0);
    char sayilar1[]="123456789";
    char sayilar2[]="101112131415161718192021222324252627282930";
    float a=1;
    for(int i =0; i<10; i++)
    {

        glRasterPos2f(a,-1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar1[i]);
        glRasterPos2f(-1,a);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar1[i]);

        glRasterPos2f(-a,-1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar1[i]);
        glRasterPos2f(-1,-a);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar1[i]);

        a+=1;


    }
    a=a-1;

    for(int i =0; i<42; i+=2)
    {


        glRasterPos2f(a-0.4,-1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i]);
        glRasterPos2f(a,-1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i+1]);


        glRasterPos2f(-1-0.4,a);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i]);
        glRasterPos2f(-1,a);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i+1]);



        glRasterPos2f(-a,-1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i]);
        glRasterPos2f(-a+0.4,-1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i+1]);



        glRasterPos2f(-1-0.4,-a);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i]);
        glRasterPos2f(-1,-a);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,sayilar2[i+1]);


        a+=1;


    }
}
void sayfayi_karelere_bol()
{
    float a=-30;
    glLineWidth(1);
    glColor3f(0.3,0.25,0.2);
    glBegin(GL_LINES);
    for(int i=0; i<60; i++)
    {
        //Dikey çizgi
        glVertex2f(a,30);
        glVertex2f(a, -30);
        //Yatay çizgi
        glVertex2f(-30,-a);
        glVertex2f(30, -a);

        a++;
    }
    glEnd();
    glFlush();
}

void koordinat_ciz_ok_ciz()
{
    glColor3f(0,0,1);
    glLineWidth(3);
    glBegin(GL_LINES);
///x eksenini çizdirmek için
    glVertex2f(-30, 0.0);
    glVertex2f(30, 0.0);

///+x ekseninin ok kodlarý
    glVertex2f(30.0, 0.0);
    glVertex2f(29.0,1.0);
    glVertex2f(30.0, 0.0);
    glVertex2f(29.0, -1.0);

///-x ekseninin ok kodlarý
    glVertex2f(-30.0, 0.0);
    glVertex2f(-29.0,1.0);
    glVertex2f(-30, 0.0);
    glVertex2f(-29, -1.0);

///y eksenini çizdirmek için
    glVertex2f(0.0, -30.0);
    glVertex2f(0.0, 30.0);

///+y ekseninin ok kodlarý
    glVertex2f(0.0, 30.0);
    glVertex2f(1.0, 29.0);
    glVertex2f(0.0, 30.0);
    glVertex2f(-1.0,29.0);
///-y ekseninin ok kodlarý
    glVertex2f(0.0,-30.0);
    glVertex2f(1.0,-29.0);
    glVertex2f(0.0,-30.0);
    glVertex2f(-1.0, -29.0);
    glEnd();
    glFlush();

}

void dosyadaki_nokta_adedi(int *adet)
{
    int x,y;
    char karakter;
    FILE *fx=fopen("nokta.txt","r");
    while(!feof(fx))
    {
        fscanf(fx,"%c %d %c %d %c %c",&karakter,&x,&karakter,&y,&karakter,&karakter);
        (*adet)++;
    }
    *adet=(*adet)-1;
    fclose(fx);
}
void dosyadan_oku_ve_noktalari_ciz(int dizi[][2],int adet)
{
    int x,y;
    char karakter;
    glColor3f(1,1,0);
    glPointSize(7);
    glBegin(GL_POINTS);
    FILE *fx=fopen("nokta.txt","r");
    fx=fopen("nokta.txt","r");
    for(int i=0; i<adet; i++)
    {
        fscanf(fx,"%c %d %c %d %c %c",&karakter,&x,&karakter,&y,&karakter,&karakter);
        dizi[i][0]=x;
        dizi[i][1]=y;
        glVertex2f(dizi[i][0],dizi[i][1]);//noktalarý ekrana çizdirdik.
    }
    fclose(fx);
    glEnd();
    glFlush();

}

void yaricap_merkezx_merkezy_bul_yaricapi_merkezi_goster(float *r,float *merkezx,float *merkezy,int dizi[][2],int adet)
{
    //toplam 2 li karþýlaþma sayýsýný bulup diziye boyut olarak verdik.
    int karsilastir=adet*(adet-1)/2.0,bx=0;
    int aradaki_uzaklik[karsilastir],xnoktalar[karsilastir][2],ynoktalar[karsilastir][2];
//for içinde en uzak iki noktayý bulduk ve n. karþýlaþmada karþýlaþtýrýlan noktalarý belirledik .
    for(int i=0; i<adet-1; i++)
    {
        for(int j=1; j<adet-i; j++)
        {
            aradaki_uzaklik[bx]=pow(dizi[i][0]-dizi[j+i][0],2)+pow(dizi[i][1]-dizi[j+i][1],2);
            xnoktalar[bx][0]=dizi[i][0];
            xnoktalar[bx][1]=dizi[j+i][0];
            ynoktalar[bx][0]=dizi[i][1];
            ynoktalar[bx][1]=dizi[j+i][1];

            bx++;
        }
    }
    int  enbuyuk=0,bizimx[2],bizimy[2];//en uzak 2 noktanýn x ve y leri
    for(int i=0; i<bx; i++)
    {
        if(aradaki_uzaklik[i]>enbuyuk)
        {
            enbuyuk=aradaki_uzaklik[i];
            bizimx[0]=xnoktalar[i][0];
            bizimx[1]=xnoktalar[i][1];
            bizimy[0]=ynoktalar[i][0];
            bizimy[1]=ynoktalar[i][1];

        }
    }



    *merkezx=(bizimx[0]+bizimx[1])/2.0;
    *merkezy=(bizimy[0]+bizimy[1])/2.0;
    *r=sqrt(pow(*merkezx-bizimx[0],2)+pow(*merkezy-bizimy[0],2));
//Çemberin üzerinde 2 nokta olup olmadýðýný anlamamýzý saðlýyor.
    float yaricapi_degis=0,r_ile_uzaklik;
    int bulunan_x,bulunan_y;
    for(int i=0; i<adet; i++)
    {

        r_ile_uzaklik=pow(dizi[i][0]-*merkezx,2)+pow(dizi[i][1]-*merkezy,2);
        if(r_ile_uzaklik>=yaricapi_degis)
            yaricapi_degis=r_ile_uzaklik;
    }
    float yaricap=sqrt(yaricapi_degis);
    if(*r==yaricap)//Eðer deðiþen yaryçap ilk yarýçapa eþitse çemberin üzerinde 2 nokta vardýr.
    {
        *r=yaricap;
        *merkezx=(bizimx[0]+bizimx[1])/2.0;
        *merkezy=(bizimy[0]+bizimy[1])/2.0;
    }


    else//Eðer deðiþen yarýçap ilk yarýçaptan büyükse çevrel çembere baþvuracaðýz.En az 3 noktada kestiðini anlýyoruz burada.
    {
        float ortax=bizimx[0]+bizimx[1],ortay=bizimy[0]+bizimy[1],enbuyukum=0,uzaklik;

        for(int i=0; i<adet; i++)
        {
            if((dizi[i][0]!=bizimx[1]&&dizi[i][1]!=bizimy[1])||(dizi[i][0]!=bizimx[0]&&dizi[i][1]!=bizimy[0]))
            {
                uzaklik=pow(dizi[i][0]-(ortax/2.0),2)+pow(dizi[i][1]-(ortay/2.0),2);
                if(uzaklik>enbuyukum)
                {
                    enbuyukum=uzaklik;
                    bulunan_x=dizi[i][0];
                    bulunan_y=dizi[i][1];
                }

            }




        }



//Çevrel çemberin merkezini ve yarýçapýný bulan matematiksel formul.

        float  akare=pow(bizimx[0],2)+pow(bizimy[0],2);
        float bkare=pow(bizimx[1],2)+pow(bizimy[1],2);
        float ckare=pow(bulunan_x,2)+pow(bulunan_y,2);

        float D=2*((bizimx[0]*(bizimy[1]-bulunan_y))+(bizimx[1]*(bulunan_y-bizimy[0]))+(bulunan_x*(bizimy[0]-bizimy[1])));

        float merkezxim=(akare*(bizimy[1]-bulunan_y)+bkare*(bulunan_y-bizimy[0])+ckare*(bizimy[0]-bizimy[1]));
        float merkezyim=(akare*(bulunan_x-bizimx[1])+bkare*(bizimx[0]-bulunan_x)+ckare*(bizimx[1]-bizimx[0]));

        *merkezx=merkezxim/D;
        *merkezy=merkezyim/D;
        *r=sqrt(pow(bulunan_x-*merkezx,2)+pow(bulunan_y-*merkezy,2));


    }
    //Merkezi göstermek için
    glColor3f(1,0,0);
    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex2f(*merkezx,*merkezy);
    glEnd();
    glFlush();

    //Yarýçapý göstermek için.
    glColor3f(1,0,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(*merkezx,*merkezy);
    glVertex2f(bizimx[0],bizimy[0]);
    glEnd();
    glFlush();
    glRasterPos2f((*merkezx+bizimx[0])/2.0+1,(*merkezy+bizimy[0])/2.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'r');


}

void cemberi_ciz(float merkezx,float merkezy,float r)
{
    glColor3f(1,1,1);
    glPointSize(2); // nokta boyutu
    glBegin(GL_POINTS);

    for( float j=-1.0 ; j<=1.0 ; j+=0.0001 )
    {
        glVertex2f(merkezx+cos(j*M_PI)*r,merkezy+sin(j*M_PI)*r);
    }

    glEnd();
    glFlush();
}
void diziyi_sirala(int dizi[][2],int adet)
{
	float temp,temp1;
    for(int i = 0; i < adet ; i++)
    {
        for(int j = 0; j < adet-i-1; j++)
        {
            if( dizi[j][0]> dizi[j+1][0])
            {
                temp = dizi[j][0];
                dizi[j][0]= dizi[j+1][0];
                dizi[j+1][0] = temp;
                temp1 = dizi[j][1];
                dizi[j][1]= dizi[j+1][1];
                dizi[j+1][1] = temp1;
            }
        }

    }
}




