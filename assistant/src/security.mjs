const encoder = new TextEncoder();
export class HttpError extends Error {
  constructor(status, message) { super(message); this.status = status; }
}
export function textField(value, name, max, min = 1) {
  if (typeof value !== 'string' || value.trim().length < min || value.length > max)
    throw new HttpError(400, `${name}需为 ${min}–${max} 个字符。`);
  return value.trim();
}
export function uuid(value) {
  if (typeof value !== 'string' || !/^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(value))
    throw new HttpError(400, '请求编号不正确，请刷新后重试。');
  return value;
}
export async function readJson(request, limit = 18000) {
  if (!request.headers.get('content-type')?.startsWith('application/json')) throw new HttpError(415, '请使用 JSON 请求。');
  const reader = request.body?.getReader();
  if (!reader) throw new HttpError(400, '请求内容为空。');
  const chunks = []; let length = 0;
  while (true) {
    const {value, done} = await reader.read();
    if (done) break;
    length += value.length;
    if (length > limit) { await reader.cancel(); throw new HttpError(413, '内容太长，请缩短后再试。'); }
    chunks.push(value);
  }
  const bytes = new Uint8Array(length); let offset = 0;
  for (const chunk of chunks) { bytes.set(chunk, offset); offset += chunk.length; }
  try { const data = JSON.parse(new TextDecoder().decode(bytes)); if (!data || typeof data !== 'object' || Array.isArray(data)) throw 0; return data; }
  catch { throw new HttpError(400, '请求格式不正确。'); }
}
const b64 = bytes => btoa(String.fromCharCode(...bytes)).replaceAll('+','-').replaceAll('/','_').replace(/=+$/,'');
const unb64 = text => Uint8Array.from(atob(text.replaceAll('-','+').replaceAll('_','/')), c => c.charCodeAt(0));
async function key(secret) {
  return crypto.subtle.importKey('raw', encoder.encode(secret), {name:'HMAC',hash:'SHA-256'}, false, ['sign','verify']);
}
export async function digest(text) {
  return b64(new Uint8Array(await crypto.subtle.digest('SHA-256', encoder.encode(text))));
}
export async function sameSecret(a, b) {
  if (!a || !b || a.length > 256) return false;
  const [x,y] = await Promise.all([digest(a),digest(b)]); let diff = 0;
  for (let i=0;i<x.length;i++) diff |= x.charCodeAt(i) ^ y.charCodeAt(i);
  return diff === 0;
}
export async function issueToken(user, secret, now = Date.now()) {
  const payload = b64(encoder.encode(JSON.stringify({...user, exp:now + 7*86400000})));
  return `${payload}.${b64(new Uint8Array(await crypto.subtle.sign('HMAC', await key(secret), encoder.encode(payload))))}`;
}
export async function verifyToken(token, secret, now = Date.now()) {
  try {
    if (!secret || typeof token !== 'string' || token.length > 2000) throw 0;
    const parts = token.split('.'); if (parts.length !== 2) throw 0;
    if (!await crypto.subtle.verify('HMAC', await key(secret), unb64(parts[1]), encoder.encode(parts[0]))) throw 0;
    const user = JSON.parse(new TextDecoder().decode(unb64(parts[0])));
    if (!Number.isFinite(user.exp) || user.exp <= now || !['student','admin'].includes(user.role) || typeof user.name !== 'string' || typeof user.id !== 'string') throw 0;
    return user;
  } catch { throw new HttpError(401, '发言凭证已失效，请重新输入邀请码。'); }
}
export function boundedSetting(value, fallback, max) {
  const parsed = Number(value); return Number.isInteger(parsed) && parsed > 0 && parsed <= max ? parsed : fallback;
}
