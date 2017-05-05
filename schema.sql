-- Adminer 4.2.4 SQLite 3 dump

DROP TABLE IF EXISTS "badges";
CREATE TABLE "badges" (
  "id" integer NOT NULL,
  "user" integer NOT NULL,
  "name" text NOT NULL,
  "date" integer NOT NULL,
  "class" integer NOT NULL,
  "tag_based" integer NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "comments";
CREATE TABLE "comments" (
  "id" integer NOT NULL,
  "post" integer NOT NULL,
  "score" integer NOT NULL,
  "text" text NOT NULL,
  "creation_date" integer NOT NULL,
  "user" integer NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "post_history";
CREATE TABLE "post_history" (
  "id" integer NOT NULL,
  "type" integer NOT NULL,
  "post" integer NOT NULL,
  "guid" text NOT NULL,
  "creation_date" integer NOT NULL,
  "user" integer NOT NULL,
  "comment" text NULL,
  "text" text NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE NO ACTION ON UPDATE NO ACTION,
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "post_links";
CREATE TABLE "post_links" (
  "id" integer NOT NULL,
  "created" integer NOT NULL,
  "source" integer NOT NULL,
  "target" integer NOT NULL,
  "type" integer NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("target") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION,
  FOREIGN KEY ("source") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "post_tags";
CREATE TABLE "post_tags" (
  "post" integer NOT NULL,
  "tag" integer NOT NULL,
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE,
  FOREIGN KEY ("tag") REFERENCES "tags" ("id") ON DELETE CASCADE
);


DROP TABLE IF EXISTS "posts";
CREATE TABLE "posts" (
  "id" integer NOT NULL,
  "title" text NULL,
  "post_type" integer NOT NULL,
  "accepted_answer" integer NULL,
  "parent" integer NULL,
  "creation_date" integer NOT NULL,
  "score" integer NOT NULL,
  "views" integer NULL,
  "body" text NOT NULL,
  "owner" integer NULL,
  "last_editor" integer NULL,
  "last_edit" integer NOT NULL,
  "last_activity" integer NOT NULL,
  "closed_at" integer NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("parent") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("owner") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("last_editor") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "tags";
CREATE TABLE "tags" (
  "id" integer NOT NULL,
  "name" text NOT NULL,
  "excerpt" integer NULL,
  "wiki" integer NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("wiki") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("excerpt") REFERENCES "posts" ("id") ON DELETE SET NULL ON UPDATE NO ACTION
);


DROP TABLE IF EXISTS "users";
CREATE TABLE "users" (
  "id" integer NOT NULL,
  "reputation" integer NOT NULL,
  "created_at" integer NOT NULL,
  "display_name" text NOT NULL,
  "last_access" integer NULL,
  "website" text NULL,
  "location" text NULL,
  "about" text NULL,
  "upvotes" integer NOT NULL,
  "downvotes" integer NOT NULL,
  "account_id" integer NOT NULL,
  PRIMARY KEY ("id")
);

CREATE UNIQUE INDEX "users_account_id" ON "users" ("account_id");


DROP TABLE IF EXISTS "votes";
CREATE TABLE "votes" (
  "id" integer NOT NULL,
  "post" integer NOT NULL,
  "type" integer NOT NULL,
  "user" integer NULL,
  "creation_date" integer NOT NULL,
  PRIMARY KEY ("id"),
  FOREIGN KEY ("user") REFERENCES "users" ("id") ON DELETE SET NULL ON UPDATE NO ACTION,
  FOREIGN KEY ("post") REFERENCES "posts" ("id") ON DELETE CASCADE ON UPDATE NO ACTION
);
