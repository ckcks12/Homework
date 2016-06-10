레퍼런싱 스트링 : 이순서로 접근한다

18쪽에서 네번째칸처럼 되려면 7을 victim으로 쫓아낸다.


본인이 구현한 부분 설명하기 (소실 발표할때)
완성된 코드랑 실행파일 가져오기 안되면 실행화면이라도 찍어올




CREATE TABLE account (
  id INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  pw TEXT NULL,
  is_student INT NULL,
  name TEXT NULL,
  email TEXT NULL,
  PRIMARY KEY(id)
);

CREATE TABLE board (
  pk INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  course_no VARCHAR(255) NOT NULL,
  title TEXT NULL,
  attach1 BLOB NULL,
  attach2 BLOB NULL,
  p_id INTEGER UNSIGNED NULL,
  timestamp TIMESTAMP NULL,
  PRIMARY KEY(pk, course_no),
  INDEX board_FKIndex1(course_no)
);

CREATE TABLE course (
  course_no VARCHAR(255) NOT NULL ,
  p_id INTEGER UNSIGNED NOT NULL,
  name TEXT NULL,
  open_year INTEGER UNSIGNED NULL,
  semester INTEGER UNSIGNED NULL,
  max_s INTEGER UNSIGNED NULL,
  PRIMARY KEY(course_no),
  INDEX course_FKIndex1(p_id)
);

CREATE TABLE course_plan (
course_no VARCHAR(255) NOT NULL ,
  PRIMARY KEY(course_no),
  course_count INTEGER UNSIGNED NOT NULL,
  course_text TEXT NULL,
  INDEX course_plan_FKIndex1(course_no)
);

CREATE TABLE course_registration (
  s_id INTEGER UNSIGNED NOT NULL,
  course_no VARCHAR(255) NOT NULL,
  PRIMARY KEY(s_id, course_no),
  INDEX account_has_course_FKIndex1(s_id),
  INDEX account_has_course_FKIndex2(course_no)
);

