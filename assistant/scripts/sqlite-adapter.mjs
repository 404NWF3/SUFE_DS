import { DatabaseSync } from 'node:sqlite';
export function localDatabase(filename=':memory:') {
  const sqlite=new DatabaseSync(filename);
  sqlite.exec('PRAGMA foreign_keys = ON');
  function prepare(sql) {
    let values=[];
    return {bind(...args){values=args;return this;},async first(){return sqlite.prepare(sql).get(...values)||null;},async all(){return {results:sqlite.prepare(sql).all(...values)};},execute(){return {success:true,meta:sqlite.prepare(sql).run(...values)};},async run(){return this.execute();}};
  }
  return {sqlite,prepare,async batch(statements){sqlite.exec('BEGIN');try {const results=statements.map(statement=>statement.execute());sqlite.exec('COMMIT');return results;}catch(error){sqlite.exec('ROLLBACK');throw error;}}};
}
