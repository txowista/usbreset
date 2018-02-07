#include <fcntl.h>
#include <unistd.h> // for close
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/usbdevice_fs.h>

int main (int argc, char **argv)
{
  char *filename;
  int fd;
  int rc;
  char str[20];
  char *pch;
  filename = (char *) calloc (20, sizeof (char));
  system ("lsusb");
  printf ("\n\nGive me pair BUS DEVICE \n");
  scanf ("%s", str);
  pch = strtok (str, "-,. ");
  strcpy (filename, "/dev/bus/usb/");
  while (pch != NULL)
    {
      strcat (filename, pch);
      pch = strtok (NULL, "-,. ");
      if(pch)strcat (filename, "/");
    }
  printf ("Direction %s\n", filename);
/*  if (argc != 2)
    {
      fprintf (stderr, "Usage: usbreset device-filename\n");
      return 1;
    }
  filename = argv[1];*/

  fd = open (filename, O_WRONLY);
  if (fd < 0)
    {
      perror ("Error opening output file");
      return 1;
    }

  printf ("Resetting USB device %s\n", filename);
  rc = ioctl (fd, USBDEVFS_RESET, 0);
  if (rc < 0)
    {
      perror ("Error in ioctl");
      return 1;
    }
  printf ("Reset successful\n");

  close (fd);
  return 0;
}
