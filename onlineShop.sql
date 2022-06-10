-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               8.0.28 - MySQL Community Server - GPL
-- Server OS:                    Win64
-- HeidiSQL Version:             11.2.0.6213
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Dumping database structure for online_shop
CREATE DATABASE IF NOT EXISTS `online_shop` /*!40100 DEFAULT CHARACTER SET latin1 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `online_shop`;

-- Dumping structure for table online_shop.cart
CREATE TABLE IF NOT EXISTS `cart` (
  `cart_id` int NOT NULL AUTO_INCREMENT,
  `user` int DEFAULT NULL,
  `created_at` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`cart_id`),
  KEY `FK_cart_user` (`user`),
  CONSTRAINT `FK_cart_user` FOREIGN KEY (`user`) REFERENCES `user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;

-- Dumping data for table online_shop.cart: ~2 rows (approximately)
/*!40000 ALTER TABLE `cart` DISABLE KEYS */;
INSERT INTO `cart` (`cart_id`, `user`, `created_at`) VALUES
	(10, 3, '2022-05-24 20:48:53'),
	(11, 4, '2022-06-07 10:51:17');
/*!40000 ALTER TABLE `cart` ENABLE KEYS */;

-- Dumping structure for table online_shop.cart_item
CREATE TABLE IF NOT EXISTS `cart_item` (
  `cart_item_id` int NOT NULL AUTO_INCREMENT,
  `cart` int DEFAULT NULL,
  `product` int DEFAULT NULL,
  `amount` int DEFAULT NULL,
  PRIMARY KEY (`cart_item_id`),
  KEY `FK__cart` (`cart`),
  KEY `FK__product` (`product`),
  CONSTRAINT `FK__cart` FOREIGN KEY (`cart`) REFERENCES `cart` (`cart_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK__product` FOREIGN KEY (`product`) REFERENCES `product` (`id_product`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;

-- Dumping data for table online_shop.cart_item: ~1 rows (approximately)
/*!40000 ALTER TABLE `cart_item` DISABLE KEYS */;
INSERT INTO `cart_item` (`cart_item_id`, `cart`, `product`, `amount`) VALUES
	(10, 10, 9, 1);
/*!40000 ALTER TABLE `cart_item` ENABLE KEYS */;

-- Dumping structure for table online_shop.category
CREATE TABLE IF NOT EXISTS `category` (
  `category_id` int NOT NULL AUTO_INCREMENT,
  `name` char(50) DEFAULT NULL,
  PRIMARY KEY (`category_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- Dumping data for table online_shop.category: ~3 rows (approximately)
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` (`category_id`, `name`) VALUES
	(1, 'Cell Phones'),
	(2, 'Computers'),
	(3, 'Bluetooth Speakers');
/*!40000 ALTER TABLE `category` ENABLE KEYS */;

-- Dumping structure for table online_shop.product
CREATE TABLE IF NOT EXISTS `product` (
  `id_product` int NOT NULL AUTO_INCREMENT,
  `name` char(50) DEFAULT NULL,
  `description` text,
  `brand` text,
  `price` double DEFAULT NULL,
  `category` int DEFAULT NULL,
  `amount` int DEFAULT NULL,
  `owner` int DEFAULT NULL,
  PRIMARY KEY (`id_product`),
  KEY `FK_product_category` (`category`),
  KEY `FK_product_user` (`owner`),
  CONSTRAINT `FK_product_category` FOREIGN KEY (`category`) REFERENCES `category` (`category_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_product_user` FOREIGN KEY (`owner`) REFERENCES `user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

-- Dumping data for table online_shop.product: ~6 rows (approximately)
/*!40000 ALTER TABLE `product` DISABLE KEYS */;
INSERT INTO `product` (`id_product`, `name`, `description`, `brand`, `price`, `category`, `amount`, `owner`) VALUES
	(1, 'Oneplus Nord 2 5G', 'Lorem ipsum', 'Oneplus', 299.99, 1, 2, 1),
	(3, 'Sounlink Revolve', 'jdsfndsiuhfiudshgfuidshLOREMIPSUM', 'Bose', 168.34, 3, 1, 1),
	(6, 'Iphone 13 Pro', 'IJOSDMSPA', 'Apple', 1299.34, 1, 1, 1),
	(7, 'Swift 3', 'aptop super coolll very fast i7, 16gb ram', 'Acer', 1300.98, 2, 3, 1),
	(9, 'kjbda', 'kjdfhsdkh', 'ciao', 123.45, 2, 1, 1),
	(12, 'Acer', 'jkdfhskjdshfkds', 'Acer', 123.54, 1, 1, 1);
/*!40000 ALTER TABLE `product` ENABLE KEYS */;

-- Dumping structure for table online_shop.role
CREATE TABLE IF NOT EXISTS `role` (
  `role_id` int NOT NULL AUTO_INCREMENT,
  `name` char(50) DEFAULT NULL,
  PRIMARY KEY (`role_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

-- Dumping data for table online_shop.role: ~2 rows (approximately)
/*!40000 ALTER TABLE `role` DISABLE KEYS */;
INSERT INTO `role` (`role_id`, `name`) VALUES
	(1, 'admin'),
	(2, 'user');
/*!40000 ALTER TABLE `role` ENABLE KEYS */;

-- Dumping structure for table online_shop.user
CREATE TABLE IF NOT EXISTS `user` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `username` char(50) DEFAULT NULL,
  `email` char(60) DEFAULT NULL,
  `password` char(50) DEFAULT NULL,
  `permission` int DEFAULT NULL,
  `created_at` datetime DEFAULT CURRENT_TIMESTAMP,
  `updated_at` datetime DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  KEY `FK_user_role` (`permission`),
  CONSTRAINT `FK_user_role` FOREIGN KEY (`permission`) REFERENCES `role` (`role_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;

-- Dumping data for table online_shop.user: ~10 rows (approximately)
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` (`user_id`, `username`, `email`, `password`, `permission`, `created_at`, `updated_at`) VALUES
	(1, 'Maximusrain', 'pol@polsl.pl', '123@as', 1, NULL, NULL),
	(2, 'Pandiu', 'plak@ksa.pl', 'as@123', 2, NULL, NULL),
	(3, 'Martynka', 'ok@mail.pl', 'pass', 2, '2022-05-09 14:03:38', '2022-05-09 14:03:39'),
	(4, 'Piast', 'poljj@mail.pl', 'pass', 2, NULL, NULL),
	(5, 'Brogu', 'masmak@plal.pl', 'Prova@123', 2, NULL, NULL),
	(7, 'PrVa forse', 'mkaosfm@mail.it', 'Prova@124', 2, NULL, NULL),
	(8, 'h', 'h', 'g', 2, '2022-05-17 11:56:09', NULL),
	(9, 'Max', 'pl@pl.pl', '123', 1, '2022-05-24 11:29:32', NULL),
	(10, 'Ele', 'ele@pl.pl', '123', 2, '2022-05-24 16:15:26', NULL),
	(15, 'jafsadfhds', 'mamsa@.iy', 'pass', 2, '2022-06-07 10:53:58', NULL);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
