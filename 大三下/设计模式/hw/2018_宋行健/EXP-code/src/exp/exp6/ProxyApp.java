package exp.exp6;

import java.lang.reflect.Proxy;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class ProxyApp extends Application {
    int func = 0;   // ������ţ�0-�ӷ���1-������2-�˷���3-����

    @Override
    public void start(Stage primaryStage) throws Exception {
        System.getProperties().put("sun.misc.ProxyGenerator.saveGeneratedFiles", "true");
        // ��̬�����������
        ICalculator calculator = new Calculator();
        MyInvocationHandler mih = new MyInvocationHandler(calculator);
        ICalculator proxyInstance = (ICalculator) Proxy.newProxyInstance(calculator.getClass().getClassLoader(), new Class[]{ICalculator.class}, mih);


        Font font = new Font(18);
        VBox layout = new VBox();
        HBox loginLayout = new HBox();
        loginLayout.setPadding(new Insets(5, 5, 5, 5));
        TextField user = new TextField();
        user.setFont(font);
        TextField password = new TextField();
        password.setFont(font);
        Button login = new Button("��½");
        login.setFont(font);
        Button logout = new Button("ע��");
        logout.setFont(font);
        logout.setDisable(true);
        loginLayout.getChildren().addAll(user, password, login, logout);

        HBox addLayout = new HBox();
        addLayout.setPadding(new Insets(5, 5, 5, 5));
        TextField d1 = new TextField();
        d1.setFont(font);
        d1.setPrefWidth(100);
        Label l1 = new Label(" + ");
        l1.setFont(font);
        TextField d2 = new TextField();
        d2.setFont(font);
        d2.setPrefWidth(100);

        Button addBtn = new Button("=");
        addBtn.setFont(font);

        // ����һ���޸ķ����İ�ť�������ť�޸ļӼ���
        Button changeBtn = new Button("�޸ķ���");
        addBtn.setFont(font);

        TextField d3 = new TextField();
        d3.setFont(font);
        d3.setPrefWidth(100);
        addLayout.getChildren().addAll(d1, l1, d2, addBtn, d3, changeBtn);

        layout.getChildren().addAll(loginLayout, addLayout);

        // �ӷ�������
        addBtn.setOnAction(e -> {
            d3.setText("");
            double v1 = Double.parseDouble(d1.getText());
            double v2 = Double.parseDouble(d2.getText());
            Object res = null;

            if (func == 0) {
                res = proxyInstance.add(v1, v2);    // ʹ�ô��������мӷ�����
            } else if (func == 1) {
                res = proxyInstance.sub(v1, v2);    // ʹ�ô��������м�������
            } else if (func == 2) {
                res = proxyInstance.multi(v1, v2);    // ʹ�ô��������м�������
            } else {
                if (v2 == 0) {
                    res = "������";
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("����ʧ��");
                    alert.setHeaderText("��������Ϊ0����");
                    alert.showAndWait();
                } else {
                    res = proxyInstance.div(v1, v2);    // ʹ�ô��������м�������
                }
            }

            if (null != res)
                d3.setText(String.valueOf(res));
            else {    // û��Ȩ�޾����
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("����ʧ��");
                alert.setHeaderText("���ȵ�¼������");
                alert.showAndWait();
            }
        });

        // �޸ķ���������л��Ӽ���
        changeBtn.setOnAction(e -> {
            d3.setText("");
            double v1 = Double.parseDouble(d1.getText());
            double v2 = Double.parseDouble(d2.getText());
            Object res = null;

            // ����
            if (func == 0) {
                l1.setText(" - ");
                func = 1;
                res = proxyInstance.sub(v1, v2);    // ʹ�ô��������м�������
            } else if (func == 1) {
                l1.setText(" X ");
                func = 2;
                res = proxyInstance.multi(v1, v2);    // ʹ�ô��������г˷�����
            } else if (func == 2) {
                l1.setText(" / ");
                func = 3;
                if (v2 == 0) {
                    res = "������";
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("����ʧ��");
                    alert.setHeaderText("��������Ϊ0����");
                    alert.showAndWait();
                } else {
                    res = proxyInstance.div(v1, v2);    // ʹ�ô��������г�������

                }
            } else {
                l1.setText(" + ");
                func = 0;
                res = proxyInstance.add(v1, v2);    // ʹ�ô��������мӷ�����
            }

            if (null != res)
                d3.setText(String.valueOf(res));
            else {    // û��Ȩ�޾����
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("����ʧ��");
                alert.setHeaderText("���ȵ�¼������");
                alert.showAndWait();
            }
        });

        // ��¼
        login.setOnAction(e -> {
            String u = user.getText();
            String pd = password.getText();
            if (Manager.getInstance().login(u, pd)) {
                user.setEditable(false);
                password.setEditable(false);
                login.setDisable(true);
                logout.setDisable(false);
                primaryStage.setTitle("����ģʽ���ѵ�½");
            }
        });

        // ע��
        logout.setOnAction(e -> {
            if (Manager.getInstance().isLogin()) {
                Manager.getInstance().logout();
                if (!Manager.getInstance().isLogin()) {
                    user.setEditable(true);
                    password.setEditable(true);
                    login.setDisable(false);
                    logout.setDisable(true);
                    primaryStage.setTitle("����ģʽ��δ��½");
                }
            }
        });

        Scene scene = new Scene(layout);
        primaryStage.setScene(scene);
        primaryStage.setTitle("����ģʽ��δ��½");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
