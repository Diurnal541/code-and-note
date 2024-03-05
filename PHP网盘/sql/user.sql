use db;
CREATE TABLE `user`(
  `user_name` varchar(60) NOT NULL,
  `password` varchar(60) NOT NULL,
  `user_folder` varchar(60) NOT NULL
);
INSERT INTO `user` (`user_name`, `password`, `user_folder`)
VALUES ('diurnal', '123456', '../users/diurnal');

