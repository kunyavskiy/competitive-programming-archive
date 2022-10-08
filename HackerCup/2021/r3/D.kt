import org.w3c.dom.events.*
import java.util.*

private class Dsu(n: Int) {
    private val p = IntArray(n) { it }
    private val size = IntArray(n) { 1 }
    private val cid = IntArray(n) { it }

    operator fun get(x: Int): Int {
        return (if (x != p[x]) get(p[x]) else x)
            .also { p[x] = it }
    }

    fun merge(x: Int, y: Int, ncid: Int) {
        val xx = get(x)
        val yy = get(y)
        require(xx != yy)
        val nroot = if (size[xx] > size[yy]) xx else yy
        val other = xx xor yy xor nroot
        p[other] = nroot
        size[nroot] = size[xx] + size[yy]
        cid[nroot] = ncid
    }

    fun getCid(x: Int) = cid[get(x)]
}


private fun solve() {
    val (r, c) = readInts()
    val a = Array(r) { readInts() }
    val s = Array(r) { readInts().toIntArray() }

    val d = Dsu(r * c)

    val evs = (0 until r).flatMap { i -> (0 until c).map { j -> i to j } }.sortedByDescending { a[it.first][it.second] }

    fun id(x: Int, y: Int) = x * c + y

    val moves = arrayOf(0 to -1, 0 to 1, 1 to 0, -1 to 0)


    val lf = MutableList(r * c) { -1 }
    val rg = MutableList(r * c) { -1 }
    val h = MutableList(r * c) { Int.MAX_VALUE }
    val p = MutableList(r * c) { -1 }

    for ((x, y) in evs) {
        for ((dx, dy) in moves) {
            val nx = x + dx
            val ny = y + dy
            if (nx in 0 until r && ny in 0 until c && a[nx][ny] >= a[x][y]) {
                val c1 = d.getCid(id(x, y))
                val c2 = d.getCid(id(nx, ny))
                if (c1 != c2) {
                    p[c1] = lf.size
                    p[c2] = lf.size
                    p.add(-1)
                    d.merge(id(x, y), id(nx, ny), lf.size)
                    lf.add(c1)
                    rg.add(c2)
                    h.add(a[x][y])
                }
            }
        }
    }

    val LOG = 20

    val up = Array(LOG) { IntArray(lf.size) { -1 } }
    for (i in lf.indices) {
        up[0][i] = p[i]
    }
    up[0][lf.size-1] = lf.size - 1
    for (lvl in 1 until LOG) {
        for (i in lf.indices) {
            up[lvl][i] = up[lvl-1][up[lvl-1][i]]
        }
    }

    fun getUp(v:Int, s:Int) : Int {
        var vv = v
        for (lvl in LOG - 1 downTo 0) {
            if (h[up[lvl][vv]] > s) {
                vv = up[lvl][vv]
            }
        }
        return vv
    }


    var ans1 = 0
    var ans2 = 0

    val tin = IntArray(lf.size)
    val rtin = IntArray(lf.size)
    val tout = IntArray(lf.size)
    var timer = 0

    //println(p)
    //println(h)

    fun dfs(v: Int) {
        if (v == -1) return
        tin[v] = timer++
        rtin[tin[v]] = v
        dfs(lf[v])
        dfs(rg[v])
        tout[v] = timer
    }
    dfs(lf.size - 1)

    val count = IntArray(lf.size)
    val active = TreeSet<Int>()

    fun Int.removeFromAns() {
        active.higher(this).let { if (it == null || tout[rtin[this]] <= it) { ans2--} }
    }
    fun Int.addToAns() {
        active.higher(this).let { if (it == null || tout[rtin[this]] <= it) { ans2++} }
    }

    fun add(id:Int) {
        if (count[id] == 0) {
            val prev = active.lower(tin[id])
            prev?.removeFromAns()
            active.add(tin[id])
            prev?.addToAns()
            tin[id].addToAns()
            //println("enable $id ${tin[id]} ${tout[id]} ${ans2}")
        }
        count[id]++
    }
    fun remove(id:Int) {
        count[id]--
        if (count[id] == 0) {
            val prev = active.lower(tin[id])
            tin[id].removeFromAns()
            prev?.removeFromAns()
            active.remove(tin[id])
            prev?.addToAns()
            //println("disable $id ${tin[id]} ${tout[id]} ${ans2}")
        }
    }

    fun addPosToAns(i:Int, j:Int) {
        if (s[i][j] < a[i][j]) {
            ans1++
            add(getUp(i * c + j, s[i][j]))
        }
    }
    fun removePosFromAns(i:Int, j:Int) {
        if (s[i][j] < a[i][j]) {
            ans1--
            remove(getUp(i * c + j, s[i][j]))
        }
    }

    for (i in 0 until r) {
        for (j in 0 until c) {
            addPosToAns(i, j)
        }
    }

    var totAns1 = 0L
    var totAns2 = 0L

    val q = readInt()

    repeat(q) {
        val (a, b, c) = readInts()
        val aa = if (it == 0) a else (a xor ans2)
        val bb = if (it == 0) b else (b xor ans2)
        val cc = if (it == 0) c else (c xor ans2)
        removePosFromAns(aa - 1, bb - 1)
        s[aa-1][bb-1] = cc
        addPosToAns(aa - 1, bb- 1)
        totAns1 += ans1
        totAns2 += ans2
        //println("!!! $ans1 $ans2")
    }


    println("$totAns1 $totAns2")
}

fun main() {
        repeat(readInt()) {
            print("Case #${it + 1}: ")
            solve()
        }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }