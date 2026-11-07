import { sqliteTable, text, integer, index } from 'drizzle-orm/sqlite-core';

export const threads = sqliteTable('threads', {
  id: text('id').primaryKey(),
  title: text('title').notNull(),
  course: text('course').notNull().default(''),
  noteId: text('note_id').notNull().default(''),
  body: text('body').notNull(),
  authorId: text('author_id').notNull(),
  authorName: text('author_name').notNull(),
  createdAt: integer('created_at').notNull(),
  updatedAt: integer('updated_at').notNull(),
  hidden: integer('hidden').notNull().default(0),
  aiStatus: text('ai_status').notNull().default('idle'),
  aiStarted: integer('ai_started').notNull().default(0),
  aiError: text('ai_error').notNull().default(''),
}, table => [index('threads_updated').on(table.hidden, table.updatedAt)]);

export const replies = sqliteTable('replies', {
  id: text('id').primaryKey(),
  threadId: text('thread_id').notNull().references(() => threads.id),
  authorId: text('author_id').notNull(),
  authorName: text('author_name').notNull(),
  kind: text('kind').notNull(),
  body: text('body').notNull(),
  sources: text('sources').notNull().default('[]'),
  createdAt: integer('created_at').notNull(),
  hidden: integer('hidden').notNull().default(0),
}, table => [index('replies_thread').on(table.threadId, table.createdAt)]);

export const budgets = sqliteTable('budgets', {
  bucket: text('bucket').primaryKey(),
  used: integer('used').notNull().default(0),
  expiresAt: integer('expires_at').notNull(),
});
