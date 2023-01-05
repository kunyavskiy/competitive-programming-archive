private const val MOD = 998244353

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

private fun solve() : ModInt {
    val n = readInt()
    val a = readInts().map { it - 1 }
    val b = readInts().map { it - 1 }

    val positions = List(n) { mutableListOf<Int>() }
    for (i in a.indices) { positions[a[i]].add(i) }
    for (i in b.indices) { positions[b[i]].add(i) }

    val deg = IntArray(n) { positions[it].size }

    val order = IntArray(n)
    var ptr = 0
    for (i in 0 until n) {
        if (deg[i] == 0) {
            return ModInt.from(0)
        }
        if (deg[i] == 1) {
            order[ptr++] = i
        }
    }

    val done = BooleanArray(n)
    var i = 0
    var j = 0
    var ans = ModInt.from(1)
    while (i < n) {
        while (i < ptr) {
            val x = order[i++]
            val position = positions[x].firstOrNull { !done[it] } ?: return ModInt.from(0)
            done[position] = true
            if (--deg[a[position]] == 1) order[ptr++] = a[position]
            if (--deg[b[position]] == 1) order[ptr++] = b[position]
        }
        while (j < n && done[j]) j++
        if (j < n) {
            order[ptr++] = a[j]
            require(deg[a[j]] == 2)
            deg[a[j]]--
            ans *= if (a[j] == b[j]) {
                ModInt.from(n)
            } else {
                ModInt.from(2)
            }
        }
    }

    return ans;
}

fun main() {
    repeat(readInt()) {
        println(solve().x)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }