struct buf {
  int valid;
  int disk;
  uint dev;
  uint blockno;
  struct sleeplock lock;
  uint refcnt;
  struct buf *next;
  uchar data[BSIZE];
  uint timestamp;
};
