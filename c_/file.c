/**文件操作
 * fopen/fclose:打开/关闭文件
 * 
 * 文本读写：
 * fprintf/fscanf:格式化读写
 * fputs/fgets,fputc/fgetc:字符串/字符读写文件
 * 
 * 二进制读写：
 * fwrite/fread
 * 
 * feof:检查是否读到结尾
 * rewind:重制文件指针到开头
 * ftell:获取当前读写指针位置，相对于头指针的偏移位置
 * fseek：偏移指针
*/
#include <stdio.h>
#include <stdlib.h>


int file_op_io(){
	FILE* txt = fopen(".gconfig","wb");
	if(!txt) printf("error: write or create file failed!\n");
	else
		fprintf(txt, "this is a test file\n这是一个测试文件");
		fclose(txt);

	txt = fopen(".gconfig","r");
	char str[6][50];
	if(!txt) printf("error: read file failed!\n");
	else
		for(int i = 0;i < 6;++i){
			fscanf(txt, "%s", str[i]);
			printf("%s ", str[i]);
		}
		fclose(txt);
	return 0;
}



int file_op_txt()
{
    FILE *fp = fopen(".test", "w+");
    // 注意: fputs不会自动添加\n
    fputs("12345678910\n", fp);
    fputs("12345678910\n", fp);
    fputs("12345678910\n", fp);

    // 将FILE结构体中的读写指针重新移动到最前面
    // 注意: FILE结构体中读写指针每读或写一个字符后都会往后移动
    rewind(fp);
    char str[1024];
    // 每次从fp中读取1024个字符, 存入到str中
    // 读取到文件末尾自动结束
    while(fgets(str, 1024, fp) && !feof(fp)){
        printf("str = %s", str);
    }
    fclose(fp);
    return 0;
}

int file_bin_io()
{
    FILE *fp = fopen("test.txt", "wb+");
    // 注意: fwrite不会关心写入数据的格式
    char *str = "lnj\0it666";
     /*
     * 第一个参数: 被写入数据指针
     * 第二个参数: 每次写入多少个字节
     * 第三个参数: 需要写入多少次
     * 第四个参数: 已打开文件结构体指针
     */
    fwrite((void *)str, 9, 1, fp);

    fclose(fp);
    return 0;
}

int main()
{

    FILE *fp = fopen("test.txt", "wb+");
    int ages[4] = {1, 3, 5, 6};
    fwrite(ages, sizeof(ages), 1, fp);
    rewind(fp);
    int data;
    while(fread(&data, sizeof(int), 1, fp) > 0){
        printf("data = %i\n", data);
    }
    return 0;
}

