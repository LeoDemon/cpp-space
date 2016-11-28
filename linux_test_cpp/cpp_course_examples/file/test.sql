select * from ur_user_info ;

START TRANSACTION;
insert into ur_user_info(user_id,user_name)values(1007, 'wangyj');
rollback;

START TRANSACTION;
delete from ur_user_info  where  user_id=1007;
rollback;

--commit;

