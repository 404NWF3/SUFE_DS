CREATE TABLE `budgets` (
	`bucket` text PRIMARY KEY NOT NULL,
	`used` integer DEFAULT 0 NOT NULL,
	`expires_at` integer NOT NULL
);
--> statement-breakpoint
CREATE TABLE `replies` (
	`id` text PRIMARY KEY NOT NULL,
	`thread_id` text NOT NULL,
	`author_id` text NOT NULL,
	`author_name` text NOT NULL,
	`kind` text NOT NULL,
	`body` text NOT NULL,
	`sources` text DEFAULT '[]' NOT NULL,
	`created_at` integer NOT NULL,
	`hidden` integer DEFAULT 0 NOT NULL,
	FOREIGN KEY (`thread_id`) REFERENCES `threads`(`id`) ON UPDATE no action ON DELETE no action
);
--> statement-breakpoint
CREATE INDEX `replies_thread` ON `replies` (`thread_id`,`created_at`);--> statement-breakpoint
CREATE TABLE `threads` (
	`id` text PRIMARY KEY NOT NULL,
	`title` text NOT NULL,
	`course` text DEFAULT '' NOT NULL,
	`note_id` text DEFAULT '' NOT NULL,
	`body` text NOT NULL,
	`author_id` text NOT NULL,
	`author_name` text NOT NULL,
	`created_at` integer NOT NULL,
	`updated_at` integer NOT NULL,
	`hidden` integer DEFAULT 0 NOT NULL,
	`ai_status` text DEFAULT 'idle' NOT NULL,
	`ai_started` integer DEFAULT 0 NOT NULL,
	`ai_error` text DEFAULT '' NOT NULL
);
--> statement-breakpoint
CREATE INDEX `threads_updated` ON `threads` (`hidden`,`updated_at`);