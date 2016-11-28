select * from UR_USER_INFO ;
select * from or_method_dict;
select * from or_module_dict;




START TRANSACTION;
insert into ur_user_info(user_id,user_name)values(1009, 'wangyj');
rollback;

START TRANSACTION;
delete from ur_user_info  where  user_id=1007;
rollback;

--commit;

select * from tables where table_name='ur_user_info';--utf8_general_ci

create table OR_METHOD_DICT
(
  method_no   VARCHAR(127) not null,
  module_id   int(9) unsigned not null,
  method_name VARCHAR(255) not null,
  method_desc VARCHAR(1024) not null,
  primary key(METHOD_NO)
)ENGINE=InnoDB AUTO_INCREMENT=1008 DEFAULT CHARSET=utf8;

create table OR_MODULE_DICT
(
  module_id   int(9) unsigned not null,
  module_name VARCHAR(255) not null,
  dll_name    VARCHAR(120) not null,
  module_desc VARCHAR(512) not null,
  PRIMARY key(module_id)
)ENGINE=InnoDB AUTO_INCREMENT=1008 DEFAULT CHARSET=utf8;


CREATE TABLE `ur_user_info` (
  `id_no` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` varchar(45) NOT NULL DEFAULT '',
  `user_name` varchar(255) NOT NULL DEFAULT '',
  `user_age` smallint(3) DEFAULT NULL,
  `remark` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`id_no`)
) ENGINE=InnoDB AUTO_INCREMENT=1008 DEFAULT CHARSET=utf8;
