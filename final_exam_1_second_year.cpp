
#include<string.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
struct thongtin{
	char hoten[20];
	char cancuoccongdan[15];
	float money;
	char stk[20]; // so tai khoan//
	char ngaythangnamsinh[15];
};
typedef struct thongtin tt;
tt x;
long size=sizeof(tt);
char user[5];
char password[5];
char *timeMoney()
{
	time_t t;
    time(&t);
    return ctime(&t);
}
void set_color( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}

void addtimeMoney(char a[],char const *sotien){
	FILE * p;
   p = fopen (a, "ab");
   time_t t;
   time(&t);
    fprintf(p, "%s%s","thoi gian thuc hien giao dich:",ctime(&t));
    fprintf(p, "%s%s\n","so tai khoan chuyen den:",a);
	fprintf(p, "%s%s\n\n","so tien da chuyen:",sotien);
   fclose(p);
}
void addtimeAdd(tt c)
{
	FILE *p;
	p=fopen("lsthem","ab");
	time_t t;
    time(&t);
	fprintf(p,"%s%s\n","ho ten:",c.hoten);
	fprintf(p,"%s%s\n","can cuoc cong dan:",c.cancuoccongdan);
	fprintf(p,"%s%s\n","so tai khoan:",c.stk);
	fprintf(p,"%s%s\n","ngay thang nam sinh:",c.ngaythangnamsinh);
	fprintf(p,"%s%s\n","thoi gian thuc hien:",ctime(&t));
	fclose(p);
}
void addtimeChange(tt c,tt d)
{
	FILE *p;
	p=fopen("change","ab");
	time_t t;
    time(&t);
	fprintf(p,"%s%s%s%s\n","ho ten:",c.hoten," chuyen thanh:",d.hoten);
	fprintf(p,"%s%s%s%s\n","can cuoc cong dan:",c.cancuoccongdan," chuyen thanh:",d.cancuoccongdan);
	fprintf(p,"%s%s%s%s\n","so tai khoan:",c.stk," chuyen thanh:",d.stk);
	fprintf(p,"%s%s%s%s\n","ngay thang nam sinh:",c.ngaythangnamsinh," chuyen thanh:",c.ngaythangnamsinh);
	fprintf(p,"%s%s\n","thoi gian thuc hien:",ctime(&t));
	fclose(p);
}
void addtimeDelete(tt c)
{
	FILE *p;
	p=fopen("delete","ab");
	time_t t;
    time(&t);
	fprintf(p,"%s%s\n","ho ten:",c.hoten);
	fprintf(p,"%s%s\n","can cuoc cong dan:",c.cancuoccongdan);
	fprintf(p,"%s%s\n","so tai khoan:",c.stk);
	fprintf(p,"%s%s\n","ngay thang nam sinh:",c.ngaythangnamsinh);
	fprintf(p,"%s%s\n","thoi gian thuc hien:",ctime(&t));
	fclose(p);
}
void readtimeMoney(char a[])
{
  FILE *p;
  char c;
   	if(( p = fopen(a,"r"))==NULL)
		{
		printf("chưa có dữ liệu của tài khoản này !");
		return ;
		}
   while(1)
   {
      c = fgetc(p);
      if(feof(p)) return;
      printf("%c", c);
   }
   fclose(p);
}
void menuif();//giao diện menu chính
void menuif1a1();// giao diện thay đổi dữ liệu
void menuif1a3();// giao diện xóa
void menuif2();// giao diện khóa tài khoản
// chưa làm
void menuif3();// giao diện xuất danh sách
void menuif4();// giao diện tìm kiếm
void menuif5();// giao diện thống kê
void menuif6();// giao diện chuyển tiền
// lởm chưa fix
void menuif7();// giao diện lịch sử
void menuif7a1();// lịch sửa thay đổi thông tin
int menuif8();// giao diện hỏi lại người dùng
void menuif9();// giao diện giao dịch thành công
// cần fix
void menu(tt x);// code menu chính
void menu1(tt x);// code menu1
void menu2(tt x);// code menu2
void menu3(tt x);// code menu3
void menu4(tt x);// code menu4
void menu5(tt x);// code menu5
void menu7(tt x);// code menu7

void login(tt x);
// phần code bên trong các chương trình
// nhập dữ liệu theo mảng
void nhap(tt &x){
		fflush(stdin);
		printf("nhập họ tên: ");
		gets(x.hoten);
		printf("nhâp số căn cước công dân: ");
		gets(x.cancuoccongdan);
		printf("nhập số tài khoản: ");
		gets(x.stk);
		printf("nhập ngày tháng năm sinh (dd/mm/yyyy):");
		gets(x.ngaythangnamsinh);
		fflush(stdin);
		printf("nhập tiền:");
		scanf("%f",&x.money);
		printf("\n");
		fflush(stdin);	
	system("cls");
	}
// thêm 1 khách hàng vào mảng
void them(tt &x)
{
	FILE *p;
	long n;
	p=fopen("mobile1","ab");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
		while(1)
	{	loop:;
		printf("nhập họ tên người thứ %d :\n",n+1);
		nhap(x);
		addtimeAdd(x);
		fwrite(&x,size,1,p);
		printf("bạn có muốn nhập tiếp không ?(nhấn c để nhập tiếp)");
		char c;
		scanf("%c",&c);
		if(c=='c') {
				++n;	goto loop;
		}
		break;
	}
	fclose(p);
}
// xuất dữ liệu theo mảng
void xuat(tt x){
	FILE *p;
	long n;
		printf("danh sách là: \n");
		printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		long i=0;
		if((p=fopen("mobile1","rb"))==NULL)
		{
		printf("chưa có dữ liệu");
		return ;
		}
		
		fseek(p,0,SEEK_END);
		n=ftell(p)/size;
		rewind(p);
		fflush(stdin);
		while(i<n){
			fread(&x,size,1,p);
			++i;
			printf("|     |                         |                    |                            |                    |             |\n");
			printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
			printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");}
		fclose(p);
}
// chỉnh sửa
void chinhsua(tt &x)
{
	FILE *p;
	int i;
	long n;
	if((p=fopen("mobile1","r+b"))==NULL)
	{
		printf("chưa có dữ liệu");
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	printf("Chỉ viết số: ");
	printf("bạn muốn sửa dữ liệu của người thứ mấy ?(n<=%d) :",n);
	scanf("%d",&i);
	
	
	
	if(i>0&&i<=n)
	{
		fseek(p,(i-1)*size,SEEK_SET);
		fread(&x,size,1,p);
		printf("dữ liệu hiện tại là:\n");
		
		printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		
		
		tt a;
		a=x;
		fflush(stdin);
		printf("bạn muốn sửa là :");
		nhap(x);
		int j;
		j=menuif8();
		switch(j)
	{
		case 1 : {
		fseek(p,(i-1)*size,SEEK_SET);
		addtimeChange(a,x);
		fwrite(&x,size,1,p);
		fclose(p);
			break;
		}
		case 2: {
			return;
		}
	}
	}
}
// duyệt danh sách
// tìm kiếm theo CCCD
void timkiemtheoCCCD(tt x)
{
	char a[20];
	FILE *p;
	long i=0;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		printf("chưa có dữ liệu");
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	fflush(stdin);
	printf("vui lòng nhập vào số CCCD của khách hàng bạn muốn tìm:");
	gets(a);
	while(i>=0&&i<=n){
		fseek(p,i*size,SEEK_SET);
		fread(&x,size,1,p);
		if(strcmp(a,x.cancuoccongdan)==0)
		{
		printf("đã tìm thấy khách hàng này, thông tin đầy đủ của khách hàng này là :\n");
		
			printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i+1,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
			getch();
			
		fclose(p);
		return;
		}
		else i++;
	}
	printf("không tìm thấy khách hàng nào có CCCD như vậy!");
	getch();
	fclose(p);
	return;
}
// tìm kiếm theo tên
void timkiemtheoten(tt x)
{
	char a[20];
	FILE *p;
	long i=0;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		printf("chưa có dữ liệu");
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	fflush(stdin);
	printf("vui lòng nhập vào họ tên của khách hàng bạn muốn tìm:");
	gets(a);
	while(i>=0&&i<=n){
		fseek(p,i*size,SEEK_SET);
		fread(&x,size,1,p);
		if(strcmp(a,x.hoten)==0)
		{
		printf("đã tìm thấy khách hàng này, thông tin đầy đủ của khách hàng này là :\n");
		
			printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i+1,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
			
			getch();
			fclose(p);
			return;
		}
		else i++;
	}
	printf("không tìm thấy khách hàng nào có tên như vậy!");
	getch();
	fclose(p);
	return;
}

// chương trình xắp xếp
void sapxeptheoten(tt x)
{
	FILE *p;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	tt a[n];
	rewind(p);
	long i=0;
	while(i<n)
	{
		fread(&x,size,1,p);
		a[i]=x;
		i++;
	}
	fclose(p);
// xắp xếp cho mảng
#define SWAP(type,x,y) do{type tmp = x; x = y; y = tmp;}while(0)
	for(int m=0;m<n-1;m++)
		for(int j=m+1;j<n;j++)
		{
		if (strcmp(a[m].hoten, a[j].hoten) > 0) SWAP(tt,a[m],a[j]); 
		}
		i=0;
// viết lại vào mảng
	p=fopen("mobile1","wb");
	i=0;
	while(i<n)
	{
		fwrite(&a[i],size,1,p);
		i++;
	}
	fclose(p);
}
// xắp xếp theo CCCD
void sapxeptheoCCCD(tt x)
{
	FILE *p;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	tt a[n];
	rewind(p);
	long i=0;
	while(i<n)
	{
		fread(&x,size,1,p);
		a[i]=x;
		i++;
	}
	fclose(p);
// xắp xếp cho mảng
#define SWAP(type,x,y) do{type tmp = x; x = y; y = tmp;}while(0)
	for(int m=0;m<n-1;m++)
		for(int j=m+1;j<n;j++)
		{
		if (strcmp(a[m].cancuoccongdan, a[j].cancuoccongdan) > 0) SWAP(tt,a[m],a[j]); 
		}
		i=0;
// viết lại vào mảng
	p=fopen("mobile1","wb");
	i=0;
	while(i<n)
	{
		fwrite(&a[i],size,1,p);
		i++;
	}
	fclose(p);
}
// thống kê những người có 200 trong tài khoản.
void thongke1(tt x)
{
	FILE *f;
	FILE *p;
	long i=0;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	fflush(stdin);
	f=fopen("thongke200","wb");
	while(i<n){
		fseek(p,i*size,SEEK_SET);
		fread(&x,size,1,p);
			if(x.money>200)
			{
				fwrite(&x,size,1,f);
			}
			i++;}
		fclose(p);
		fclose(f);
}
// khóa tài khoản 1
void khoataikhoan1()
{
	// mục đích là xuất ra danh sách những tài khoản chưa có lịch sử giao dịch
	FILE *f;
	FILE *p;
	FILE *k;
	long i=0;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	fflush(stdin);
	f=fopen("chuacolsgd","ab");
	while(i<n){
		fseek(p,i*size,SEEK_SET);
		fread(&x,size,1,p);
			if((k=fopen(x.stk,"rb"))==NULL)
			{
				fwrite(&x,size,1,f);
				fclose(k);
			}
			i++;
			}
		fclose(p);
		fclose(f);
}
void xuatkhoataikhoan1()
{
		FILE *p;
		long n;
		printf("danh sách tài khoản chưa có lịch sử giao dịch là: \n");
        printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		long i=0;
		if((p=fopen("chuacolsgd","rb"))==NULL)
		{
		printf("chưa có dữ liệu");
		return ;
		}
		fseek(p,0,SEEK_END);
		n=ftell(p)/size;
		rewind(p);
		fflush(stdin);
		while(i<n){
			fread(&x,size,1,p);
			++i;
		printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");}
		fclose(p);
}
// khóa tài khoản 2
void khoataikhoan2()
{
	// mục đích là xóa những tài khoản có 0 đồng trong tài khoản và chưa có lịch sử giao dịch
	FILE *f;
	FILE *p;
	FILE *molsgd;
	long i=0;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	fflush(stdin);
	f=fopen("taikhoanbikhoa","ab");
	fseek(p,0,SEEK_END);// đọc từu đầu đến cuối file 
	n=ftell(p)/size;
	tt a[n];
	rewind(p);// cho con trỏ quay về đầu file
	while(i<n)
	{
		fread(&x,size,1,p);
		a[i]=x;
		i++;
	}
	fclose(p);
fflush(stdin);
for(int k=0;k<n;k++){
		if((molsgd=fopen(a[k].stk,"rb"))==NULL&&a[k].money==0)
		{
			fwrite(&a[k],size,1,f);
			fclose(molsgd);
		for(int m=k;m<n-1;m++){
		a[m]=a[m+1];
		}
	n--;
	}
}
// viết lại vào mảng
	p=fopen("mobile1","wb");
	i=0;
	while(i<n)
	{
		fwrite(&a[i],size,1,p);
		i++;
	}
		fclose(p);
		fclose(f);
}
void xuatkhoataikhoan2()
{
		FILE *p;
		long n;
		printf("danh sách tài khoản bị khóa là: \n");
		printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		long i=0;
		if((p=fopen("taikhoanbikhoa","rb"))==NULL)
		{
		printf("chưa có dữ liệu");
		return ;
		}
		fseek(p,0,SEEK_END);
		n=ftell(p)/size;
		rewind(p);
		fflush(stdin);
		while(i<n){
			fread(&x,size,1,p);
			++i;
		printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");}
		fclose(p);
}
//xuất thống kê 1
void xuatthongke1(tt x){
		FILE *f;
		if((f=fopen("thongke200","rb"))==NULL)
			{
			printf("chưa có dữ liệu");
			return ;
			}
		printf("danh sách những người có trên 200 $ trong tài khoản là: \n");
		printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		long i=0;
		long n;
		fseek(f,0,SEEK_END);
		n=ftell(f)/size;
		rewind(f);
		fflush(stdin);
		while(i<n){
			fread(&x,size,1,f);
			++i;
			printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");}
		fclose(f);
}
// chương trình chuyển tiền
void chuyentien(tt x)
{
	FILE *p;
	long n;
	long i=0;
	char c[20];
	if((p=fopen("mobile1","rb"))==NULL)
	{
		printf("chưa có dữ liệu");
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);
	n=ftell(p)/size;
	tt a[n];
	fflush(stdin);
	printf("vui lòng nhập vào số tài khoản:");
	gets(c);
	rewind(p);
	while(i<n)
		{
			fread(&x,size,1,p);
			a[i]=x;
			i++;
		}
	fclose(p);
	i=0;
	while(i<n)
	{
		if(strcmp(c,a[i].stk)==0)
		{
			char *sotien;
			system("cls");
			printf("họ và tên:%20s\t\tsố tài khoản:%20s\n",a[i].hoten,a[i].stk);
			fflush(stdin);
			printf("nhập số tiền bạn muốn chuyển:");
			gets(sotien);
			fflush(stdin);
			int k=menuif8();
			if(k==1)
			{

			for(int t=0;t<n;t++)	if(strcmp(c,a[t].stk)==0) a[t].money=a[t].money+atof(sotien);
			printf("đã thực hiện giao dịch thành công đến số tài khoản %s",c);
			printf("\nsố tiền đã chuyển %f",atof(sotien));
			printf("\nthời gian thực hiện giao dịch %s",timeMoney());
			addtimeMoney(c,sotien);
			i=0;
			p=fopen("mobile1","wb");
				while(i<n)
				{
					fwrite(&a[i],size,1,p);
					i++;
				}
				fclose(p);
				return;
			}
			else return;
		}
		i++;
	}
		printf("không tìm thấy khách hàng nào có số tài khoản như vậy");
		fclose(p);
		return;
 } 
// xóa tài khoản theo tên
void xoaname(tt x){
	FILE *p;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		printf("chưa có dữ liệu");
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);// đọc từ đầu đến cuối file 
	n=ftell(p)/size;
	tt a[n];
	rewind(p);// cho con trỏ quay về đầu file
	long i=0;
	while(i<n)
	{
		fread(&x,size,1,p);
		a[i]=x;
		i++;
	}
	fclose(p);
fflush(stdin);
printf("nhập tên khách hàng bạn muốn xóa: ");
char b[20];
gets(b);
for(int k=0;k<n;k++){
	if(strcmp(a[k].hoten,b)==0){
		tt z=a[k];
		printf("đã xóa khách hàng này!");
		addtimeDelete(z);
		for(int m=k;m<n-1;m++){
		a[m]=a[m+1];
		}
	n--;
	}
}

// viết lại vào mảng
	p=fopen("mobile1","wb");
	i=0;
	while(i<n)
	{
		fwrite(&a[i],size,1,p);
		i++;
	}
	fclose(p);
}
// xóa tài khoản theo CCCD
void xoaCCCD(tt x){
	FILE *p;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		printf("chưa có dữ liệu");
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);// đọc từu đầu đến cuối file 
	n=ftell(p)/size;
	tt a[n];
	rewind(p);// cho con trỏ quay về đầu file
	long i=0;
	while(i<n)
	{
		fread(&x,size,1,p);
		a[i]=x;
		i++;
	}
	fclose(p);
fflush(stdin);
printf("nhập số CCCD của khách hàng bạn muốn xóa: ");
char b[20];
gets(b);
for(int k=0;k<n;k++){
	if(strcmp(a[k].cancuoccongdan,b)==0){
		tt z=a[k];
		printf("đã xóa khách hàng này!");
		addtimeDelete(z);
		for(int m=k;m<n-1;m++){
		a[m]=a[m+1];
		}
	n--;
	}	
}
// viết lại vào mảng
	p=fopen("mobile1","wb");
	i=0;
	while(i<n)
	{
		fwrite(&a[i],size,1,p);
		i++;
	}
	fclose(p);
}
// thống kê 2
void thongke2(tt x){
	FILE *p;
	long n;
	if((p=fopen("mobile1","rb"))==NULL)
	{
		
		return;
	}
	system("cls");
	fseek(p,0,SEEK_END);// đọc từu đầu đến cuối file và để con trỏ ở cuối file
	n=ftell(p)/size;
	tt a[n];
	rewind(p);// cho con trỏ quay về đầu file
	long i=0;
	long j=0;
	while(i<n)
	{
		fread(&x,size,1,p);
		a[i]=x;
		i++;
	}
	fclose(p);
// viết vào file
	FILE *l;
	l=fopen("thongke2","wb");
	for(int k=0;k<n;k++)
	{
		if(a[k].money<0)	fwrite(&a[k],size,1,l);
	}
	fclose(l);
}
// xuất của thống kê 2
void xuatthongke2(tt x){
		FILE *p;
 printf("danh sách những tài khoản bị âm tiền là: \n");
       
		printf(" _____________________________________________________________________________________________________________________\n");
	    printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5s|%-29s|%-20s|%-31s|%-25s|%-0s\n","STT","[họ và tên]","[CCCD]","[ngày tháng năm sinh]","[số tài khoản]","[số dư cuối] |");
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");
		long n;
		long i=0;
		if((p=fopen("thongke2","rb"))==NULL)
		{
		printf("chưa có dữ liệu");
		return ;
		}
		fseek(p,0,SEEK_END);
		n=ftell(p)/size;
		rewind(p);
		fflush(stdin);
		while(i<n){
			fread(&x,size,1,p);
			++i;
		printf("|     |                         |                    |                            |                    |             |\n");
		printf("|%-5d|%-25s|%-20s|%-28s|%-20s|%12.1f |\n",i,x.hoten,x.cancuoccongdan,x.ngaythangnamsinh,x.stk,x.money);
		printf("|_____|_________________________|____________________|____________________________|____________________|_____________|\n");}
		fclose(p);}
main()
{
	SetConsoleOutputCP(65001);    
	login(x);
}
void menuif()
{
	printf("                                                                   ______                               \n");
	printf("                                                     |\\       /|  |         |\\    |  |     |           \n");
	printf("                                                     | \\     / |  |______   | \\   |  |     |           \n");
	printf("                                                     |  \\   /  |  |         |  \\  |  |     |           \n");
	printf("                                                     |   \\ /   |  |         |   \\ |  |     |           \n");
	printf("                                                     |    \\    |  |______   |    \\|  |_____|           \n");
	
	printf("                                 __________________________________________________________________________\n");
	printf("                                |                                   |     |                                |\n");
	printf("                                |         1.thay đổi dữ liệu        |     |     5.thống kê                 |\n");
	printf("                                |                                   |     |                                |\n");
	printf("                                |         2.khóa tài khoản          |     |     6.chuyển tiền              |\n");
	printf("                                |                                   |     |                                |\n");
	printf("                                |         3.xuất danh sách          |     |     7.lịch sử                  |\n"); 
	printf("                                |                                   |     |                                |\n");
	printf("                                |         4.tìm kiếm khách hàng     |     |     8.thoát                    |\n");
	printf("                                |___________________________________|_____|________________________________|\n");
	
	}
void menuif1a1()
{
	system("cls");
	printf("                                 ________________________________________________________\n");
	printf("                                |                                                        |\n");
	printf("                                |              1. thêm khách hàng mới                    |\n");
	printf("                                |                                                        |\n");
	printf("                                |              2. chỉnh sử thông tin khách hàng          |\n");
	printf("                                |                                                        |\n");
	printf("                                |              3. xóa tài khoản khách hàng               |\n");
	printf("                                |                                                        |\n");
	printf("                                |              4. quay lại menu                          |\n");
	printf("                                |________________________________________________________|\n");
}
void menuif1a3(){
	system("cls");
printf("                                       _________________________________________________\n");
printf("                                      |                                                 |\n");
printf("                                      |           1. xoá theo tên                       |\n");
printf("                                      |                                                 |\n");
printf("                                      |           2. xoá theo căn cước công dân         |\n");
printf("                                      |                                                 |\n");
printf("                                      |           3. quay lại menu                      |\n");
printf("                                      |_________________________________________________|\n");
}
void menuif2()
{
printf("                                       _________________________________________________\n");
printf("                                      |                                                 |\n");
printf("                                      |       1. tài khoản chưa có lịch sử giao dịch    |\n");
printf("                                      |                                                 |\n");
printf("                                      |       2. khóa tài khoản khách hàng              |\n");
printf("                                      |                                                 |\n");
printf("                                      |       3. quay lại menu                          |\n");
printf("                                      |_________________________________________________|\n");
}
void menuif3()
{
	system("cls");
	printf("                                   _________________________________________________\n");
	printf("                                  |                                                 |\n");
	printf("                                  |          1. xắp xếp theo tên                    |\n");
	printf("                                  |                                                 |\n");
	printf("                                  |          2. xắp xếp theo căn cước công dân      |\n");
	printf("                                  |                                                 |\n");
	printf("                                  |          3. quay lại menu                       |\n");
	printf("                                  |_________________________________________________|\n");
}
void menuif4()
{
	system("cls");
	printf("                                   _________________________________________________\n");
	printf("                                  |                                                 |\n");
	printf("                                  |          1. tìm kiếm theo tên                   |\n");
	printf("                                  |                                                 |\n");
	printf("                                  |          2. tìm kiếm theo căn cước công dân     |\n");
	printf("                                  |                                                 |\n");
	printf("                                  |          3. quay lại menu                       |\n");
	printf("                                  |_________________________________________________|\n");	}
void menuif5()
{
	system("cls");
	printf("                                   _________________________________________________________________\n");
	printf("                                  |                                                                 |\n");
	printf("                                  |            1. số người có số dư trên 200$ trong tài khoản       |\n");
	printf("                                  |                                                                 |\n");
	printf("                                  |            2. danh sách đen                                     |\n");
	printf("                                  |                                                                 |\n");
	printf("                                  |            3. quay lại menu                                     |\n");
	printf("                                  |_________________________________________________________________|\n");
}
void menuif7()
{
system("cls");
	printf("                                   ______________________________________________\n");
	printf("                                  |                                              |\n");
	printf("                                  |         1. lịch sử giao dịch                 |\n");
	printf("                                  |                                              |\n");
	printf("                                  |         2. lịch sử chỉnh sửa thông tin       |\n");
	printf("                                  |                                              |\n");
	printf("                                  |         3. quay lại menu                     |\n");
	printf("                                  |______________________________________________|\n");
}
void menuif7a2()
{
	system("cls");
	printf("                                   _____________________________________________________\n");
	printf("                                  |                                                     |\n");
	printf("                                  |           1. lịch sử thêm khách hàng                |\n");
	printf("                                  |                                                     |\n");
	printf("                                  |           2. lịch sử xóa khách hàng                 |\n");
	printf("                                  |                                                     |\n");
	printf("                                  |           3. lịch sử thay đổi thông tin khách hàng  |\n");
	printf("                                  |                                                     |\n");
	printf("                                  |           4. quay lại menu                          |\n");
	printf("                                  |_____________________________________________________|\n");
}
int menuif8()
{
	system("cls");
	printf("                                  _____________________________________________________________________\n");
    printf("                                  |                                                                   |\n");	
	printf("                                  |    bạn có chắc chắn muốn thực hiện hành động này không?           |\n");
	printf("                                  |                                                                   |\n");
	printf("                                  |          1. có                 2. không                           |\n");
	printf("                                  |                                                                   |\n");
	printf("                                  |___________________________________________________________________|\n\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2)
	{
		printf("chỉ có thể nhập 1 hoặc 2 hãy nhập lại!\n");
		scanf("%d",&i);
		system("cls");
	}
	return i;
}
void menuif9()
{
	printf("                                   ____________________________________________________________\n");
	printf("                                  |                                                        | B |\n");
	printf("                                  |         Bạn đã thực hiện giao dịch thành công!         | A |\n");
	printf("                                  |            ~ Cảm ơn bạn đã sử dụng dịch vụ  ~          | N |\n");
	printf("                                  |________________________________________________________|_K_|\n");
}
void menu1(tt x)
{
	menuif1a1();
	printf("                                 ____________________________________________________________\n");
	printf("                                |                                                            |\n");
	printf("                                |   Vui lòng bấm nút tương ứng để chọn 1 trong các mục sau!  |\n");
	printf("                                |____________________________________________________________|\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3&&i!=4)
	{
		system("cls"); 
		menuif1a1();
		printf("\nbạn đã nhập sai nút, hãy nhập lại!\n");
		scanf("%d",&i);
	}
	switch(i)
	{
	case 1:
		{// tạo khách hàng mới
		them(x);
		break;
		}
	case 2:
		{// chỉnh sửa khách hàng
		chinhsua(x);
		getch();
		break;
		}
	case 3:
		{// xóa tài khoản vĩnh viễn
		menuif1a3();
		printf("\n");
		int i;
		printf("vui lòng chọn kiểu xóa dữ liệu !\n");
		scanf("%d",&i);
			switch(i)
			{
				// theo tên
				case 1:
				{
					xoaname(x);
					getch();
					break;
				}
				// theo số CCCD
				case 2:
				{
					xoaCCCD(x);
					getch();
					break;
				} 
			}
		break;
	}
	case 4:{
		break;
	}
}
}
void menu2(tt x)
{
	menuif2();
	printf("\nvui lòng bấm nút tương ứng để chọn 1 trong các mục sau!\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3)
	{
		system("cls");
		menuif2();
		printf("\nbạn đã nhập sai nút, hãy nhập lại!\n");
		scanf("%d",&i);
	}
	switch(i)
				{
					case 1:
						{
							khoataikhoan1();
							xuatkhoataikhoan1();
							getch();
							break;
						}
					case 2:
						{
							khoataikhoan2();
							xuatkhoataikhoan2();
							getch();
							break;
						}
				}
}
void menu3(tt x)
{
		menuif3();
	printf("vui lòng bấm nút tương ứng để chọn 1 trong các mục sau!\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3)
	{
		system("cls");
		menuif3();
		printf("\nbạn đã nhập sai nút, hãy nhập lại!\n");
		scanf("%d",&i);
	}
	switch(i)
				{
					case 1:
						{
							sapxeptheoten(x);
							xuat(x);
							getch();
							break;
						}
					case 2:
						{
							sapxeptheoCCCD(x);
							xuat(x);
							getch();
							break;
						}
				}
}
void menu4(tt x)
{
		menuif4();
	printf("vui lòng bấm nút tương ứng để chọn 1 trong các mục sau!\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3)
	{
		system("cls");
		menuif4();
		printf("\nbạn đã nhập sai nút, hãy nhập lại!\n");
		scanf("%d",&i);
	}
	switch(i)
				{
					case 1:
						{
							timkiemtheoten(x);
							getch();
							break;
						}
					case 2:
						{
							timkiemtheoCCCD(x);
							getch();
							break;
						}
				}
}
void menu5(tt x)
{
		menuif5();
	printf("vui lòng bấm nút tương ứng để chọn 1 trong các mục sau!\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3)
	{
		system("cls");
		menuif5();
		printf("\nbạn đã nhập sai nút, hãy nhập lại!\n");
		scanf("%d",&i);
	}
	switch(i)
				{
					case 1:
						{
							system("cls");
							thongke1(x);
							xuatthongke1(x);
							getch();
							break;
						}
					case 2:
						{
							system("cls");
							thongke2(x);
							xuatthongke2(x);
							getch();
							break;
						}
				}
}
void menu7(tt x)
{
	menuif7();
	printf("vui lòng bấm nút tương ứng để chọn 1 trong các mục sau!\n");
	int i;
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3)
	{
		system("cls"); 
		menuif7();
		printf("\nbạn đã nhập sai nút, hãy nhập lại!\n");
		scanf("%d",&i);
	}
					switch(i)
					{
						case 1:
						{
							fflush(stdin);
							char a[20];
							printf("vui lòng nhập vào số tài khoản bạn muốn kiểm tra lịch sử giao dịch:");
							gets(a);
							system("cls");
							readtimeMoney(a);
							getch();
							break;
						}
						case 2:
						{
							menuif7a2();
							int i;
							scanf("%d",&i);
							while(i!=1&&i!=2&&i!=3&&i!=4)
							{
								system("cls"); 
								menuif7a2();
								printf("\nbạn đã nhập sai nút, hãy nhập lại!");
								scanf("%d",&i);
							}
							switch(i)
							{
								case 1:
									{
										system("cls");
										char a[]="lsthem";
										readtimeMoney(a);
										getch();
										break;
									}
								case 2:
								{
									system("cls");
									char a[]="delete";
									readtimeMoney(a);
									getch();
									break;
								}
								case 3:
								{
									system("cls");
									char a[]="change";
									readtimeMoney(a);
									getch();
									break;
								}
								case 4: return;
							}
							break;
						}
					}	

}
void menu(tt x)
{	
	while (true)
	{	
		system("cls");
		menuif();
		printf("vui lòng bấm nút tương ứng để chọn một trong các mục sau!\n");
		int i;
		scanf("%d",&i);
		while(i!=1&&i!=2&&i!=3&&i!=4&&i!=5&&i!=6&&i!=7&&i!=8)
		{
			system("cls");
			printf("bạn đã nhập sai nút hãy nhập lại!\n");
			menuif();
			scanf("%d",&i);
		}
		switch(i)
		{
			// thay đổi dữ liệu
			case 1:
				{
					system("cls");
					menu1(x);
					break;
				}
			// khóa tài khoản
			case 2:
				{
				
				system("cls");
				menu2(x);
				break;
				}
			// xuất danh sách
			case 3:
			{
				//sắp xếp
				system("cls");
					menu3(x);
					break;
			}
			case 4:
			{
				// tìm kiếm
				system("cls");
				menu4(x);
				break;
			}
			case 5:
			{
				// thống kê
				system("cls");
				menu5(x);
				break;
			}
			case 6:{
				// chuyển tiền
				chuyentien(x);
				getch();
				break;
			}
			case 7:{
				system("cls");
				menu7(x);
				break;
			}
			case 8:
			{
				printf("cảm ơn bạn đã sử dụng dịch vụ của chúng tôi");
				getch();
			return ;
			}
		}
	}
}
void login(tt x){
	printf("                                   ____________________________________________________________\n");
	printf("                                  |     __________________________________________________      |\n");
	printf("                                  |    |       <BANKING ACCOUNT MANAGEMENT SYSTEM>        |     |\n");
	printf("                                  |    |            ~       BCP BANK       ~              |     |\n");
	printf("                                  |    |                                                  |     |\n");
	printf("                                  |    |                    WELCOME!                      |     |\n");
	printf("                                  |    |__________________________________________________|     |\n");
	printf("                                  |                           ______       ||                   |\n");
	printf("                                  |                          |      |      ||                   |\n");
	printf("                                  |                      ___|________|__   ||                   |\n");
	printf("                                  |                        | O  O    |     ||                   |\n");
	printf("                                  |          ___________   |  __     |     ||                   |\n");
	printf("                                  |         |    $$$    |  |   ___   |     ||                   |\n");
	printf("                                  |         |___________|  |__|   |__|     ||                   |\n");
	printf("                                  |_____________________________________________________________|\n");
	
	getch();
	printf("bạn có phải là admin không?\n");
	printf("                                       _____________________________________________________\n");
	printf("                                      |                           |                         |\n");
	printf("                                      |         (1. có )          |        (2. không)       |\n");
	printf("                                      |___________________________|_________________________|\n");
	int a;
	scanf("%d",&a);
	if (a==1) goto loop;
	else
	{
		printf("chương trình này chỉ dành cho admin!");
		return;
	}
	loop:;
	fflush(stdin);
	system("cls");
	printf("*************ĐĂNG NHẬP*************\n");
	printf("TÀI KHOẢN:");
	gets(user);
	printf("MẬT KHẨU:");
	gets(password);
		int i=0;
		while(true)
		{
			int a=strcmp(user,"3.14");
			int b=strcmp(password,"3.14");
			
					if(a==0&&b==0)
						{   system("cls");
							printf("                                            __________________________________\n");
							printf("                                           |                                  |\n");
							printf("                                           |        ĐĂNG NHẬP THÀNH CÔNG      |\n");
							printf("                                           |__________________________________|\n");
							getch();
							system("cls");
							menu(x);
							return;
						}					
					else
						{
							i++;
							printf("đăng nhập thất bại, hãy nhập lại MẬT KHẨU!\n");
							getch();
							system("cls");
							printf("*************ĐĂNG NHẬP*************\n");
							printf("TÀI KHOẢN:");
							gets(user);
							printf("MẬT KHẨU:");
							gets(password);
							if(i==3) 
							{
										printf("BẠN ĐÃ NHẬP SAI MẬT KHẨU QUÁ SỐ LẦN CHO PHÉP TIẾN HÀNH KHÓA CHƯƠNG TRÌNH");
										return;                                   
							} 
						}
		}
					
	}