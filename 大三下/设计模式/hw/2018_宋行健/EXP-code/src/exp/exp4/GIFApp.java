package exp.exp4;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Cursor;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.File;
import java.nio.file.Paths;

public class GIFApp extends Application {
    // ��Ļλ���Լ��ֺ�
    double textX = 50;
    double textY = 50;
    int textSizeInt = 32;


    Frame[] frames = null;
    String[] texts = null;
    VBox textParent = null;
    int time = 100;
    boolean playing = false;


    @Override
    public void start(Stage primaryStage) throws Exception {
        // ҳ����
        double viewWidth = 680;
        double viewHeight = 400;

        // ��д��
        IGIFReader reader = new GIFReader();
        IGIFWriter writer = new GIFWriter();

        // �ܲ���
        SplitPane layout = new SplitPane();

        // չʾ�����ı�������򲼾�
        VBox viewLayout = new VBox();
        VBox textLayout = new VBox();

        // �ļ�ѡ������
        HBox fileLayout = new HBox();
        fileLayout.setPadding(new Insets(10));
        Label label = new Label("�ļ���");
        label.setFont(new Font(16));
        TextField filePath = new TextField();
        filePath.setEditable(false);
        filePath.setPrefWidth(viewWidth * 0.8);
        Button browse = new Button("���..");
        fileLayout.getChildren().addAll(label, filePath, browse);
        HBox.setMargin(filePath, new Insets(0, 10, 0, 10));
        FileChooser fileChooser = new FileChooser();
        fileChooser.setInitialDirectory(new File(".")); // ����Ĭ�ϴ�λ��Ϊ��ǰ�����·��
        fileChooser.setTitle("ѡ��̬ͼƬ");
        fileChooser.getExtensionFilters().addAll(new ExtensionFilter("��ͼ", "*.gif"));

        // ��������
        Canvas canvas = new Canvas(viewWidth, viewHeight);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        HBox playLayout = new HBox();
        Slider slider = new Slider();
        slider.setShowTickMarks(true);
        slider.setShowTickLabels(true);
        slider.setBlockIncrement(1);
        slider.setMajorTickUnit(1);
        slider.setPrefWidth(viewWidth * 0.9);
        Button playBtn = new Button("����");
        playLayout.getChildren().addAll(slider, playBtn);
        VBox.setMargin(canvas, new Insets(10, 10, 10, 10));


        // ��Ļ�������
        Button addTextBtn = new Button("�����Ļ");
        addTextBtn.setFont(new Font(16));
        addTextBtn.setPrefWidth(130);
        VBox.setMargin(addTextBtn, new Insets(10, 10, 10, 10));
        ScrollPane scrp = new ScrollPane();
        textParent = new VBox();
        scrp.setContent(textParent);
        Button saveBtn = new Button("������̬ͼƬ");
        saveBtn.setPrefWidth(130);
        saveBtn.setFont(new Font(16));
        VBox.setMargin(saveBtn, new Insets(10, 10, 10, 10));
        // ��ɫѡ����
        Label label1 = new Label("��ѡ����Ļ��ɫ: ");
        ColorPicker colorPicker = new ColorPicker();
        VBox.setMargin(colorPicker, new Insets(10, 10, 10, 10));
        colorPicker.setValue(Color.RED);
        // �ֺ�����
        Label label2 = new Label("�������ֺ�: ");
        TextField textSize = new TextField();
        textSize.setText("32");
        textSize.setPrefWidth(50);
        textSizeInt = Integer.parseInt(textSize.getText());

        // �������
        viewLayout.getChildren().addAll(fileLayout, canvas, playLayout);
        textLayout.getChildren().addAll(label1, colorPicker, label2, textSize, addTextBtn, scrp, saveBtn);
        layout.getItems().addAll(viewLayout, textLayout);


        // ������ťѡ���ļ�·��
        browse.setOnAction(e -> {
            File selectedFile = fileChooser.showOpenDialog(primaryStage);
            if (selectedFile != null) {
                filePath.setText(selectedFile.getAbsolutePath());
                frames = reader.read(selectedFile.getAbsolutePath());
                texts = new String[frames.length];
                // ��ȡGif�Ŀ�ߣ����޸Ĵ��ڿ��
                gc.drawImage(frames[0].getImage(), 0, 0, frames[0].getWidth(), frames[0].getHeight());
                canvas.setWidth(frames[0].getWidth());
                canvas.setHeight(frames[0].getHeight());
                viewLayout.setPrefWidth(frames[0].getWidth());
                layout.setPrefWidth(frames[0].getWidth() * 1.3);
                slider.setMax(frames.length - 1);
                slider.setValue(0);
            }
        });

        // �����Ļ�༭ģ��
        addTextBtn.setOnAction(e -> {
            TextPane tp = new TextPane(textParent);
            tp.setOnInputMethodTextChanged(te -> updateText());
            textParent.getChildren().add(tp);
            textSizeInt = Integer.parseInt(textSize.getText());
            // ��Ⱦ
            Render.rendering(canvas, frames[0], texts[0], textX, textY, colorPicker.getValue(), textSizeInt);
        });


        // �����鿴ÿ֡ͼƬ
        slider.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> arg0, Number oldValue, Number newValue) {
                if (frames != null) {
                    int i = newValue.intValue();
                    Render.rendering(canvas, frames[i], texts[i], textX, textY, colorPicker.getValue(), textSizeInt);
                }
            }
        });

        // ���Ŷ�̬ͼƬ
        playBtn.setOnAction(e -> {
            textSizeInt = Integer.parseInt(textSize.getText()); // ���������С
            if (frames != null && !playing) {
                updateText();
                Timeline tl = new Timeline();
                tl.setCycleCount(frames.length);
                tl.getKeyFrames().add(new KeyFrame(Duration.millis(time), new EventHandler<ActionEvent>() {
                    int i = 0;
                    @Override
                    public void handle(ActionEvent arg0) {
                        slider.setValue(i);
                        Render.rendering(canvas, frames[i], texts[i], textX, textY, colorPicker.getValue(), textSizeInt);
                        i++;
                        if (i < frames.length) {
                            time = frames[i].getDelay();
                        }
                    }
                }));
                tl.play();
                playing = true;
                tl.setOnFinished(fe -> {
                    slider.setValue(0);
                    Render.rendering(canvas, frames[0], texts[0], textX, textY, colorPicker.getValue(), textSizeInt);
                    playing = false;
                });
            }
        });

        // ������̬ͼƬ
        saveBtn.setOnAction(e -> {
            if (frames != null) {
                String fileName = filePath.getText().replaceAll(".gif", "_new.gif");
                System.out.println("����·��: " + fileName);
                Frame[] output = new Frame[frames.length];
                textSizeInt = Integer.parseInt(textSize.getText()); // ���������С
                for (int i = 0; i < frames.length; i++) {
                    Image img = Render.rendering(canvas, frames[i], texts[i], textX, textY, colorPicker.getValue(), textSizeInt);
                    assert img != null;
                    output[i] = new Frame(img, frames[i].getDelay());
                }
                // ������ʾ
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("����ɹ�");
                alert.setHeaderText("����·��");
                alert.setContentText(fileName);
                alert.showAndWait();
                writer.write(output, fileName);
            }else{
                // ������ʾ
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("����ʧ��");
                alert.setHeaderText("δѡ��ͼƬ");
                alert.showAndWait();
            }
        });

        // �϶�����
        canvas.setCursor(Cursor.MOVE);
        canvas.addEventHandler(MouseEvent.MOUSE_DRAGGED, event -> {
            textX = event.getX();
            textY = event.getY();
            textSizeInt = Integer.parseInt(textSize.getText()); // ���������С
            Render.rendering(canvas, frames[0], texts[0], textX, textY, colorPicker.getValue(), textSizeInt);
        });

        Scene scene = new Scene(layout, 860, 500);
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.getIcons().add(new Image(Paths.get("bin/images/res/gif.png").toUri().toString()));
        primaryStage.setTitle("��Ӷ�ͼ��Ļ");
        primaryStage.show();
    }


    public void updateText() {
        if (frames != null) {
            texts = new String[frames.length];
            for (Node tp : textParent.getChildren()) {
                TextPane temp = (TextPane) tp;
                int start = Integer.parseInt(temp.getStart().getText());
                int end = Integer.parseInt(temp.getEnd().getText());
                // ���������Χ
                if (start < 0 || end > frames.length) {
                    // ������ʾ
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("����");
                    alert.setHeaderText("֡��Χ����");
                    alert.showAndWait();
                } else {
                    // ������ʾ
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setTitle("�ɹ�");
                    alert.setHeaderText("�����Ļ�ɹ�");
                    alert.setContentText("�ӵ� " + start + " ֡���� " + end + " ֡\n�����Ļ��" + temp.getContent().getText());
                    alert.showAndWait();
                    for (int i = start; i <= end; i++) {
                        texts[i] = temp.getContent().getText();
                    }
                }
            }
        }
    }


    public static void main(String[] args) {
        launch(args);
    }

}
