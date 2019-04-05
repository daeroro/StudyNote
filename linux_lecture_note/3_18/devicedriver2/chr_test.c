#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#define DEVICE_NAME             "mydrv"
#define MYDRV_MAX_LENGTH        4096 //page 사이즈 만큼 쓰기 위해서 
#define MIN(a, b)               (((a) < (b)) ? (a) : (b))

struct class *myclass;
struct cdev *mycdev;
struct device *mydevice;
dev_t mydev;

static int *write_ret;
int *read_ret;
char *mydrv_data;
int mydrv_read_offset, mydrv_write_offset;

static int mydrv_open(struct inode *, struct file *);
static int mydrv_release(struct inode *, struct file *);
static ssize_t mydrv_read(struct file *, char *, size_t, loff_t *);
static ssize_t mydrv_write(struct file *, const char *, size_t, loff_t *);

static int mydrv_open(struct inode *inode, struct file *file)
{
        printk("%s\n", __FUNCTION__);
        return 0;
}

static int mydrv_release(struct inode *inode, struct file *file)
{
        printk("%s\n", __FUNCTION__);
        return 0;
}

static ssize_t mydrv_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
#if 0
        if((buf == NULL) || (count < 0))
                return -EINVAL;
        if(mydrv_write_offset - mydrv_read_offset <= 0)
                return 0;
        count = MIN((mydrv_write_offset - mydrv_write_offset), count);
        if(copy_to_user(buf, mydrv_data + mydrv_read_offset, count))
                return -EFAULT;
        mydrv_read_offset += count;
#endif
        int i;

        read_ret = (int *)kmalloc(sizeof(int), GFP_KERNEL);
        read_ret[0] = 1;

        for(i = 1; i <= count; i++)
                read_ret[0] *= i;

        return read_ret[0];
}

static ssize_t mydrv_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
#if 0
        if((buf == NULL) || (count < 0))
                return -EINVAL;
        if(count + mydrv_write_offset >= MYDRV_MAX_LENGTH)
                return 0;
        if(copy_from_user(mydrv_data + mydrv_write_offset, buf, count))
                return -EFAULT;
        mydrv_write_offset += count;
#endif
        int i;

        write_ret = (int *)kmalloc(sizeof(int), GFP_KERNEL);
        write_ret[0] = 0;

        for(i = 1; i <= count; i++)
                write_ret[0] += i;

        return write_ret[0];
}

struct file_operations mydrv_fops = {
#if 0
        .owner = THIS_MODULE,
        .read = mydrv_read,
        .write = mydrv_write,
        .open = mydrv_open,
        .release = mydrv_release,
#endif
	//THIS_MODULE,
	read: mydrv_read,
	write: mydrv_write,
	open: mydrv_open,
	release: mydrv_release,
};

int mydrv_init(void)
{
		//커널 함수이므로 커널 코드 분석 해야함
		//일반적으로 사용하는 패턴이므로 그대로 가져다 써도 됨
		//캐릭터 디바이스를 등록
        if(alloc_chrdev_region(&mydev, 0, 1, DEVICE_NAME) < 0)
                return -EBUSY;

		//드라이버 종류를 설정
		//만들 드라이버가 gpio이면 gpio.. 등등
        myclass = class_create(THIS_MODULE, "mycharclass");
        if(IS_ERR(myclass))
        {
				//에러가 났을 때 등록 해제
                unregister_chrdev_region(mydev, 1);
                return PTR_ERR(myclass);
        }
	
		// dev/ 장치 파일 밑에 "mydevicefile"이 생성됨
        mydevice = device_create(myclass, NULL, mydev, NULL, "mydevicefile");
        if(IS_ERR(mydevice))
        {
				// 설정한 드라이버의 종류를 해제하고 등록을 해제함
                class_destroy(myclass);
                unregister_chrdev_region(mydev, 1);
                return PTR_ERR(mydevice);
        }

		// 실제 드라이버가 구동할 공간을 할당
		//실제 메모리를 할당 받아 옴
        mycdev = cdev_alloc();
		// file_operations 아래에 함수 포인터를 wrapping 함
		// 내가 만든 드라이버의 함수 동작으로 설정
        mycdev->ops = &mydrv_fops;
        mycdev->owner = THIS_MODULE;
		
		// 실제 장치 파일간의 연동을 수행하기 위해 관리 체인에 추가
		// 관리체인 : 드라이버를 관리하기 위해 사용하는 연결 리스트
        if(cdev_add(mycdev, mydev, 1) < 0)
        {
                device_destroy(myclass, mydev);
                class_destroy(myclass);
                unregister_chrdev_region(mydev, 1);
                return -EBUSY;
        }
		
		// 실제 드라이버 내부에서 활용하기 위한 버퍼를 할당함
		// kmalloc 이므로 Buddy 및 Slab 을 활용하게 되어 있음
        mydrv_data = (char *)kmalloc(MYDRV_MAX_LENGTH * sizeof(char), GFP_KERNEL);
        mydrv_read_offset = mydrv_write_offset = 0;
        return 0;
}

void mydrv_cleanup(void)
{
		//등록했던 것 등을 free 해줌 - 항상 일정한 절차임
        kfree(mydrv_data);
        cdev_del(mycdev);
        device_destroy(myclass, mydev);
        class_destroy(myclass);
        unregister_chrdev_region(mydev, 1);
}

module_init(mydrv_init);
module_exit(mydrv_cleanup);
MODULE_LICENSE("GPL");
