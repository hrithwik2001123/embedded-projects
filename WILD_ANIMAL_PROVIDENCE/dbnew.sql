/*
SQLyog Community v13.0.1 (64 bit)
MySQL - 5.1.32-community : Database - wildanimal_intrusion
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`wildanimal_intrusion` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `wildanimal_intrusion`;

/*Table structure for table `animals` */

DROP TABLE IF EXISTS `animals`;

CREATE TABLE `animals` (
  `id` int(100) NOT NULL AUTO_INCREMENT,
  `user_id` int(100) NOT NULL,
  `animal_name` varchar(255) NOT NULL,
  `animal_image` varchar(255) NOT NULL,
  `timestamp` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

/*Data for the table `animals` */

insert  into `animals`(`id`,`user_id`,`animal_name`,`animal_image`,`timestamp`) values 
(1,1,'cat','static/images/captured_image_20250207_151837.jpg','2025-02-07 15:18:36'),
(2,1,'elephant','static/images/captured_image_20250207_153229.jpg','2025-02-07 15:32:27'),
(3,1,'dog','static/images/captured_image_20250207_154104.jpg','2025-02-07 15:41:03'),
(4,1,'elephant','static/images/captured_image_20250207_162507.jpg','2025-02-07 16:25:06');

/*Table structure for table `login` */

DROP TABLE IF EXISTS `login`;

CREATE TABLE `login` (
  `id` int(100) NOT NULL AUTO_INCREMENT,
  `email` varchar(100) DEFAULT NULL,
  `password` varchar(100) DEFAULT NULL,
  `usertype` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

/*Data for the table `login` */

insert  into `login`(`id`,`email`,`password`,`usertype`) values 
(1,'mee@gmail.com','12345','user'),
(2,'Rin@gmail.com','1256','user'),
(3,'rinsha@gmail.com','123456','user'),
(4,'fghh','456','user'),
(5,'ghhj','hhh','user'),
(6,'admin@gmail.com','admin123','admin'),
(7,NULL,NULL,NULL);

/*Table structure for table `notifications` */

DROP TABLE IF EXISTS `notifications`;

CREATE TABLE `notifications` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `animal_name` varchar(255) NOT NULL,
  `timestamp` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

/*Data for the table `notifications` */

insert  into `notifications`(`id`,`user_id`,`animal_name`,`timestamp`) values 
(1,1,'cat','2025-02-07 15:18:36'),
(2,1,'elephant','2025-02-07 15:32:27'),
(3,1,'dog','2025-02-07 15:41:03'),
(4,1,'elephant','2025-02-07 16:25:06');

/*Table structure for table `porttable` */

DROP TABLE IF EXISTS `porttable`;

CREATE TABLE `porttable` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `portaddress` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

/*Data for the table `porttable` */

insert  into `porttable`(`id`,`portaddress`) values 
(1,'192.168.230.155');

/*Table structure for table `registration` */

DROP TABLE IF EXISTS `registration`;

CREATE TABLE `registration` (
  `id` int(100) NOT NULL AUTO_INCREMENT,
  `first_name` varchar(100) DEFAULT NULL,
  `last_name` varchar(100) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  `location` varchar(100) DEFAULT NULL,
  `phonenumber` varchar(100) DEFAULT NULL,
  `login_id` int(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

/*Data for the table `registration` */

insert  into `registration`(`id`,`first_name`,`last_name`,`address`,`email`,`location`,`phonenumber`,`login_id`) values 
(1,'meenu','minsha','thiruvannur','mee@gmail.com','Kozhikode','+919496144222',1),
(2,'Aysha','Rinsha','olavanna','Rin@gmail.com','calicut ','+919638524178',2),
(3,'rinsha','rinu','kozhikode','rinsha@gmail.com','eranjipalam','+919876543234',3),
(4,'fg33','dg33','ggh','fghh','fhhj','+919685742358',4),
(5,'tty4566','567','hji','ghhj','566','+916958253696',5);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
