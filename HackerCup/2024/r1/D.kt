/*private const val MOD =  998244353

@JvmInline
@Suppress("NOTHING_TO_INLINE")
private value class ModInt(val x: Int) {
    inline operator fun plus(other: ModInt) = ModInt((x + other.x).let { if (it >= MOD) it - MOD else it })
    inline operator fun minus(other: ModInt) = ModInt((x - other.x).let { if (it < 0) it + MOD else it })
    inline operator fun times(other: ModInt) = ModInt((x.toLong() * other.x % MOD).toInt())
    fun power(p_: Int): ModInt {
        var a = this
        var res = ModInt(1)
        var p = p_
        while (p != 0) {
            if ((p and 1) == 1) res *= a
            a *= a
            p = p shr 1
        }
        return res
    }

    inline operator fun div(other: ModInt) = this * other.inv()
    inline fun inv() = power(MOD - 2)

    companion object {
        inline fun from(x: Int) = ModInt((x % MOD + MOD) % MOD)
        inline fun from(x: Long) = ModInt(((x % MOD).toInt() + MOD) % MOD)
    }
}

@JvmInline
private value class ModIntArray(private val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private fun compute(s: String): Int {
    val dp = ModIntArray(s.length + 1) { ModInt.from(0) }
    dp[0] = ModInt.from(1);
    for (i in 0 until s.length) {
        if (s[i] != '0') {
            dp[i + 1] += dp[i]
            if (i + 2 <= s.length && s.substring(i..i + 1).toInt() in 1..26)
                dp[i+2] += dp[i]
        }
    }
    return dp[s.length].x
}

private fun solve() {
    val (s, k_) = readStrings()
    var k = k_.toInt()
    k -= 1
    val sfixed = s.replace('?', '1')
    val need1 = BooleanArray(sfixed.length+1)
    val need2 = BooleanArray(sfixed.length+1)
    for (i in s.indices) {
        if (s[i] != '0') {
            need1[i] = true
            if (i + 1 != s.length && sfixed.substring(i..i+1).toInt() in 1..26) need2[i] = true
        }
    }
    val reachableP = BooleanArray(sfixed.length + 1)
    reachableP[0] = true
    for (i in s.indices) {
        if (reachableP[i]) {
            if (need1[i]) reachableP[i+1] = true
            if (need2[i]) reachableP[i+2] = true
        }
    }
    val reachableS = BooleanArray(sfixed.length + 1)
    reachableS[s.length] = true
    for (i in s.length downTo 1) {
        if (reachableS[i]) {
            if (need1[i - 1]) reachableS[i - 1] = true
            if (i != 1 && need2[i - 2]) reachableS[i - 2] = true
        }
    }
    for (i in 0 until s.length) {
        if (!reachableP[i] || !reachableS[i + 1]) {
            need1[i] = false
        }
        if (i + 2 <= s.length && (!reachableP[i] || !reachableS[i + 2])) {
            need2[i] = false
        }
    }
    val dp = Array(10) { IntArray(s.length) }
    fun can(pos: Int, value:Int, next:Int) : Boolean {
        if (s[pos] != '?' && (s[pos] - '0') != value) return false
        if ((need1[pos] || need2[pos]) && value == 0) return false
        if (need2[pos] && (value * 10 + next) !in 1..26) return false
        return true
    }
    for (i in 0 until 10) {
        if (can(s.length - 1, i, -100)) {
            dp[i][s.length - 1] = 1
        }
    }
    for (pos in s.length - 2 downTo 0) {
        for (value in 0..9) {
            for (next in 0..9) {
                if (can(pos, value, next)) {
                    dp[value][pos] += dp[next][pos + 1]
                    dp[value][pos] = minOf(dp[value][pos], k + 1)
                }
            }
        }
    }
    val ans = IntArray(s.length) { -1 }

    for (i in 0 until s.length) {
        for (value in 9 downTo 0) {
            if (i > 0 && !can(i-1, ans[i-1], value)) continue
            if (dp[value][i] <= k) {
                k -= dp[value][i]
            } else {
                ans[i] = value
                break
            }
        }
        require(ans[i] != -1)
    }

    val result = ans.joinToString("")

    println("$result ${compute(result)}")
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
 */