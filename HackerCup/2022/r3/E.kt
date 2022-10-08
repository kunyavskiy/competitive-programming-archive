import com.sun.source.util.TreeScanner
import com.sun.source.util.Trees
import java.util.*
import kotlin.math.*

private const val LCA_LOG = 20

private class LCA {
    val ups = mutableListOf(IntArray(LCA_LOG))
    val h = mutableListOf(0)
    val children = mutableListOf(mutableListOf<Int>())
    val hashes = mutableListOf(0L)

    fun lca(u: Int, v: Int) : Int {
        val a = preLca(u, v) ?: return if (h[u] < h[v]) u else v
        return ups[a.first][0]
    }

    fun getUp(u: Int, h: Int) : Int {
        var uu = u
        for (i in LCA_LOG - 1 downTo 0) {
            if ((h and (1 shl i)) != 0) {
                uu = ups[uu][i]
            }
        }
        return uu
    }

    fun preLca(u: Int, v:Int): Pair<Int, Int>? {
        var uu = getUp(u, maxOf(0, h[u] - h[v]))
        var vv = getUp(v, maxOf(0, h[v] - h[u]))
        require(h[uu] == h[vv])
        if (uu == vv) return null
        for (i in LCA_LOG- 1 downTo 0) {
            if (ups[uu][i] != ups[vv][i]) {
                uu = ups[uu][i]
                vv = ups[vv][i]
            }
        }
        require(ups[uu][0] == ups[vv][0]) {
            "OH"
        }
        return uu to vv
    }

    fun addVertex(p: Int) {
        children[p].add(h.size)
        h.add(h[p] + 1)
        children.add(mutableListOf())
        hashes.add(0L)
        val x = IntArray(LCA_LOG)
        ups.add(x)
        x[0] = p
        for (i in 1 until LCA_LOG) {
            x[i] = ups[x[i - 1]][i - 1]
        }
    }

    private fun dfs(v:Int) {
        children[v].forEach(::dfs)
        children[v].sortBy { hashes[it] }
        var hash = children.size.toLong()
        for (i in children[v]) {
            hash = hash * 23917L + hashes[i]
        }
        hashes[v] = hash
    }

    fun buildHashes() {
        dfs(0)
        for (i in 1 until  hashes.size) {
            hashes[i] += hashes[ups[i][0]] * 31
        }
    }
}

data class Point(val x:Int, val y: Int)

fun cross(x1:Int, y1:Int, x2:Int, y2:Int) = x1.toLong() * y2.toLong() - x2.toLong() * y1.toLong()

private class Segment private constructor(val p1: Point, val p2:Point, val polyId: Int) : Comparable<Segment> {
    init { require(p1.y <= p2.y) }
    override fun compareTo(other: Segment): Int {
        if (toTheRight(other.p1) || toTheRight(other.p2)) return -1
        if (toTheLeft(other.p1) || toTheLeft(other.p2)) return 1
        if (other.toTheRight(p1) || other.toTheRight(p2)) return 1
        if (other.toTheLeft(p1) || other.toTheLeft(p2)) return -1
        return 0
    }

    fun toTheLeft(p: Point) = inY(p) && cross(p2.x - p1.x, p2.y - p1.y, p.x - p1.x, p.y - p1.y) > 0
    fun toTheRight(p: Point) = inY(p) && cross(p2.x - p1.x, p2.y - p1.y, p.x - p1.x, p.y - p1.y) < 0
    fun inY(p:Point) = p1.y <= p.y && p.y <= p2.y

    override fun toString() = "Segment($p1, $p2, $polyId)"

    companion object {
        fun from(p1: Point, p2:Point, index:Int ) = if (p1.y < p2.y) Segment(p1, p2, index) else Segment(p2, p1, index)
    }
}

private fun List<Point>.area() : Long {
    var ans = 0L
    for (i in indices) {
        val p1 = get(i)
        val p2 = get(if (i == lastIndex) 0 else i + 1)
        ans += cross(p1.x, p1.y, p2.x, p2.y)
    }
    return abs(ans)
}

private class LeftestFinder(val ys: IntArray) {
    val lst = computeLst(ys.size)
    val segs = MutableList(2 * lst) { TreeSet<Segment>() }
    val allSegs = mutableListOf<Segment>()

    companion object {
        fun computeLst(n: Int): Int {
            var x = 1
            while (x <= n) x *= 2
            return x
        }
    }

    fun getSeq(y: Int) = buildList {
        var v = 1
        var l = 0
        var r = lst
        add(segs[0])
        while (r - l > 1) {
            val m = (l + r) / 2
            if (m < ys.size && ys[m] <= y) {
                v = 2 * v + 1
                l = m
            } else {
                v = 2 * v
                r = m
            }
            add(segs[v])
        }
    }

    fun findToTheLeft(p: Point): Int {
        val lst = getSeq(p.y)
        val ans = lst.mapNotNull { it.floor(Segment.from(p, p, -1)) }.max()
        return ans.polyId
    }
    fun findToTheRight(p: Point) : Int {
        return getSeq(p.y).mapNotNull { it.ceiling(Segment.from(p, p, -1)) }.min().polyId
    }
    private fun update(v: Int, l: Int, r: Int, L: Int, R: Int, p: Segment) {
        if (r <= L || R <= l) return
        if (L <= l && r <= R) {
            segs[v].add(p)
            return
        }
        val m = (l + r) / 2
        update(2 * v, l, m, L, R, p)
        update(2 * v + 1, m, r, L, R, p)
    }

    fun add(p: Segment) {
        allSegs.add(p)
        if (p.p1.y != p.p2.y) {
            update(1, 0, lst, ys.binarySearch(p.p1.y), ys.binarySearch(p.p2.y), p)
        }
    }
}

private fun solve() {
    val BIG = 1_000_000_001
    val bigPoly = listOf(Point(-1, -1), Point(-1, BIG), Point(BIG, BIG), Point(BIG, -1))
    val polygons = MutableList(readInt()) {
        val m = readInt()
        val cs = readInts()
        List(m) {
            Point(cs[2 * it], cs[2 * it + 1])
        }
    }.apply { add(bigPoly) }
        .sortedByDescending { it.area() }

    val finder = LeftestFinder(polygons.flatten().map { it.y }.distinct().sorted().toIntArray())

    val lca = LCA()
    for ((index, p) in polygons.withIndex()) {
        if (index != 0) {
            val leftId = finder.findToTheLeft(p.minBy { it.x })
            val rightId = finder.findToTheRight(p.maxBy { it.x })
            lca.addVertex(lca.lca(leftId, rightId))
        }
        for (i in p.indices) {
            val p1 = p[i]
            val p2 = p[if (i == p.lastIndex) 0 else i + 1]
            finder.add(Segment.from(p1, p2, index))
        }
    }
    //println(lca.ups.indices.map { it to lca.ups[it][0] })
    lca.buildHashes()
    val q = readInt()
    var ans = 0
    fun Point.locate() = lca.lca(
        finder.findToTheLeft(this),
        finder.findToTheRight(this)
    )
    var ee = 0
    for (unused in 0 until q) {
        val (x1, y1, x2, y2, e) = readInts()
        val a = Point(x1 xor ee, y1 xor ee).locate()
        val b = Point(x2 xor ee, y2 xor ee).locate()
        if (lca.hashes[a] == lca.hashes[b]) {
            ans += 1
            ee = ee xor e
        }
    }
    println(ans)
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