package exp.exp3;

import java.io.File;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

import javafx.geometry.Point2D;
import javafx.scene.image.Image;
import javafx.scene.media.AudioClip;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.transform.Rotate;

public class GameManager {
    // ����ģʽ��������ģʽ
    private static final GameManager instance = new GameManager();
    private Map map;
    private Player player;
    private Coin coinPrototype;    // ���ԭ��
    private List<Coin> coinList;
    private Number[] numbers;
    private List<Number> number;
    private int score;
    private int frameNum;
    AudioClip ac;
    MediaPlayer mp;
    // ���ƽ�������ٶȣ��ۼ�ȡģ�жϣ�
    private static int coinSpeedController = 1;
    private static final int coinSpeed = 5;

    private GameManager() {
        initialize();
    }

    // ��ʼ������Ԫ��
    private void initialize() {
        // ������ͼ����
        setMap(new Map(new Image(Paths.get("bin\\images\\map02.png").toUri().toString())));
        getMap().setHorizonY(550);

        // ������ɫ����
        DynamicImage rImg = new DynamicImage();
        DynamicImage lImg = new DynamicImage();
        File file = Paths.get("bin\\images\\saber").toFile();
        for (File f : Objects.requireNonNull(file.listFiles())) {
            Image img = new Image(f.toURI().toString());
            rImg.add(img);
            lImg.add(ImageTool.rotate(img, 180, Rotate.Y_AXIS));
        }
        setPlayer(new Player(lImg, rImg));
        getPlayer().setPosition(new Point2D(100, getMap().getHorizonY() - getPlayer().getHeight()));

        // �������ԭ�Ͷ���
        DynamicImage lookList = new DynamicImage();
        Image img = new Image(Paths.get("bin\\images\\res\\res03.png").toUri().toString());
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                lookList.add(ImageTool.clipImage(img, 64 * i, 64 * j, 64, 64));
            }
        }
        setCoinPrototype(new Coin(lookList));
        setCoinList(new ArrayList<Coin>()); // ��ʼ���������

        // ��ʼ����������
        Image numberSrc = new Image(Paths.get("bin\\images\\res\\res04.png").toUri().toString());
        setNumbers(new Number[10]);
        for (int i = 0; i < 10; i++) {
            getNumbers()[i] = new Number(ImageTool.clipImage(numberSrc, 36 * i, 0, 36, 40), i);
        }
        setNumber(new ArrayList<Number>());
        setScore(0);

        // ��ʼ����������������Ч
        ac = new AudioClip(Paths.get("bin\\musics\\m001.mp3").toUri().toString());
        mp = new MediaPlayer(new Media(Paths.get("bin\\musics\\m002.mp3").toUri().toString()));
        mp.setCycleCount(MediaPlayer.INDEFINITE);
        mp.play();

        // ��Ϸ֡����ʼ��
        setFrameNum(0);
    }

    public void update() {
        move();
        judge();
        refresh();
    }

    // ˢ��������ң����
    public void refresh() {
        coinSpeedController++;
        if (coinSpeedController % coinSpeed == 0) {
            coinSpeedController /= coinSpeed;
            Coin copy = null;
            try {
                copy = (Coin) getCoinPrototype().clone();
                copy.setPosition(new Point2D(20 + Math.random() * (getMap().getWidth() - 20 - copy.getWidth()), 0));
                getCoinList().add(copy);
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
        }
    }

    // ʵ��仯����
    public void move() {
        getPlayer().move();
        for (Coin c : coinList) {
            c.move();
        }
    }

    // �÷��ж�������Ƹ���
    public void judge() {
        // �÷��ж�
        Iterator<Coin> iter = getCoinList().iterator();
        while (iter.hasNext()) {
            Coin c = iter.next();
            if (c.getPosition().getY() > (getMap().getHorizonY() - c.getHeight())) {
                iter.remove();
            } else {
                if (getPlayer().isOverlap(c)) {
                    ac.play();
                    setScore(getScore() + 1);
                    iter.remove();
                }
            }
        }

        // �����Ƹ���
        number.clear();
        int temp = getScore();
        String[] strList = Integer.toString(temp).split("");    // �ָ�����λ��
        for (int i = 0; i < strList.length; i++) {
            int n = Integer.parseInt(strList[strList.length - i - 1]);
            Number num = null;
            try {
                num = (Number) numbers[n].clone();
                num.setPosition(new Point2D(getMap().getWidth() - 10 - (i + 1) * num.getWidth(), 10));
                number.add(num);
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
        }
    }

    public static GameManager getManager() {
        return instance;
    }

    public Map getMap() {
        return map;
    }

    public void setMap(Map map) {
        this.map = map;
    }

    public Player getPlayer() {
        return player;
    }

    public void setPlayer(Player player) {
        this.player = player;
    }

    public Coin getCoinPrototype() {
        return coinPrototype;
    }

    public void setCoinPrototype(Coin coinPrototype) {
        this.coinPrototype = coinPrototype;
    }

    public List<Coin> getCoinList() {
        return coinList;
    }

    public void setCoinList(List<Coin> coinList) {
        this.coinList = coinList;
    }

    public Number[] getNumbers() {
        return numbers;
    }

    public void setNumbers(Number[] numbers) {
        this.numbers = numbers;
    }

    public List<Number> getNumber() {
        return number;
    }

    public void setNumber(List<Number> number) {
        this.number = number;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public int getFrameNum() {
        return frameNum;
    }

    public void setFrameNum(int frameNum) {
        this.frameNum = frameNum;
    }

    public AudioClip getAc() {
        return ac;
    }

    public void setAc(AudioClip ac) {
        this.ac = ac;
    }


}
